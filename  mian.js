// Importa o módulo axios para fazer requisições HTTP
const axios = require('axios');

// URL base do servidor
const baseURL = 'http://localhost:8080';

// Função para adicionar um plano de investimento
const addInvestmentPlan = async (plan) => {
    try {
        const response = await axios.post(`${baseURL}/add-plan`, plan);
        console.log('Plano adicionado com sucesso:', response.data);
    } catch (error) {
        console.error('Erro ao adicionar plano:', error.response ? error.response.data : error.message);
    }
};

// Função para realizar um investimento
const invest = async (investment) => {
    try {
        const response = await axios.post(`${baseURL}/invest`, investment);
        console.log('Investimento realizado com sucesso:', response.data);
    } catch (error) {
        console.error('Erro ao realizar investimento:', error.response ? error.response.data : error.message);
    }
};

// Função para autenticar uma mensagem
const authenticateMessage = async (messageHash) => {
    try {
        const response = await axios.post(`${baseURL}/authenticate-message`, { message_hash: messageHash });
        console.log('Mensagem autenticada com sucesso:', response.data);
    } catch (error) {
        console.error('Erro ao autenticar mensagem:', error.response ? error.response.data : error.message);
    }
};

// Exemplo de uso das funções
const exampleUsage = async () => {
    // Adiciona um plano de investimento
    const plan = {
        plan_name: 'economicPlan',
        initial_investment: 500,
        monthly_return: 5,
        annual_return: 60,
        net_annual_return: 300,
        slots: 500
    };
    await addInvestmentPlan(plan);

    // Realiza um investimento
    const investment = {
        plan_name: 'economicPlan',
        amount: 100,
        investor_address: '0x3333333333333333333333333333333333333333'
    };
    await invest(investment);

    // Autentica uma mensagem
    const messageHash = '0xabcdef1234567890abcdef1234567890abcdef1234567890abcdef1234567890';
    await authenticateMessage(messageHash);
};

// Executa o exemplo de uso
exampleUsage();
