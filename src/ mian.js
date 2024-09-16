// Importa os módulos necessários
const express = require('express');
const { exec } = require('child_process');
const axios = require('axios');
const app = express();

// Define a porta do servidor
const PORT = 8080;

// Middleware para processar JSON no corpo das requisições
app.use(express.json());

// Função para executar o programa C que processa a IA e CRM
const runCProgram = (token, crmData, callback) => {
    const command = `./backend/main ${token} ${crmData.join(' ')}`;  // Chama o programa C
    exec(command, (error, stdout, stderr) => {
        if (error) {
            callback(error, null);
        } else {
            callback(null, stdout);
        }
    });
};

// Rota para adicionar um plano de investimento
app.post('/add-plan', async (req, res) => {
    const { token, plan_name, initial_investment, crm_data } = req.body;

    // Executa o programa em C com o token NSC e dados de CRM
    runCProgram(token, crm_data, (error, result) => {
        if (error) {
            res.status(500).send('Erro no processamento IA');
        } else {
            // Faz a requisição HTTP para adicionar o plano de investimento (exemplo de resposta)
            axios.post('http://localhost:8080/external-api/add-plan', { plan_name, initial_investment })
                .then(response => {
                    res.send(`Plano adicionado com sucesso: ${result}`);
                })
                .catch(err => {
                    res.status(500).send('Erro ao comunicar com a API externa');
                });
        }
    });
});

// Rota para realizar um investimento
app.post('/invest', (req, res) => {
    const { plan_name, amount, investor_address } = req.body;

    // Faz a requisição HTTP para o endpoint de investimento
    axios.post('http://localhost:8080/external-api/invest', { plan_name, amount, investor_address })
        .then(response => {
            res.send(`Investimento realizado com sucesso: ${response.data}`);
        })
        .catch(err => {
            res.status(500).send('Erro ao realizar investimento');
        });
});

// Rota para autenticar uma mensagem usando IA
app.post('/authenticate-message', (req, res) => {
    const { message_hash } = req.body;

    // Executa o programa em C para autenticar a mensagem
    runCProgram('TOKEN_NSC', [message_hash], (error, result) => {
        if (error) {
            res.status(500).send('Erro ao autenticar a mensagem');
        } else {
            res.send(`Mensagem autenticada: ${result}`);
        }
    });
});

// Inicia o servidor
app.listen(PORT, () => {
    console.log(`Servidor rodando na porta ${PORT}`);
});
