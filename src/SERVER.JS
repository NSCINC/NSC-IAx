const express = require('express');
const sqlite3 = require('sqlite3').verbose();
const bodyParser = require('body-parser');

// Cria uma instância do aplicativo Express
const app = express();
const port = process.env.PORT || 8080;

// Configura o body-parser para processar o JSON
app.use(bodyParser.json());

// Conecta ao banco de dados SQLite em memória
const db = new sqlite3.Database(':memory:');

// Cria a tabela de planos de investimento
db.serialize(() => {
  db.run(`CREATE TABLE investment_plans (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    plan_name TEXT NOT NULL UNIQUE,
    initial_investment INTEGER NOT NULL,
    monthly_return INTEGER NOT NULL,
    annual_return INTEGER NOT NULL,
    net_annual_return INTEGER NOT NULL,
    slots INTEGER NOT NULL
  )`);
});

// Função para adicionar um plano de investimento
const addPlan = (planName, initialInvestment, monthlyReturn, annualReturn, netAnnualReturn, slots, callback) => {
  const stmt = db.prepare(`INSERT INTO investment_plans (plan_name, initial_investment, monthly_return, annual_return, net_annual_return, slots)
                           VALUES (?, ?, ?, ?, ?, ?)`);
  stmt.run(planName, initialInvestment, monthlyReturn, annualReturn, netAnnualReturn, slots, function(err) {
    callback(err);
  });
  stmt.finalize();
};

// Função para obter um plano de investimento
const getPlan = (planName, callback) => {
  db.get(`SELECT * FROM investment_plans WHERE plan_name = ?`, [planName], (err, row) => {
    callback(err, row);
  });
};

// Rota para adicionar um plano de investimento
app.post('/add-plan', (req, res) => {
  const { plan_name, initial_investment, monthly_return, annual_return, net_annual_return, slots } = req.body;

  addPlan(plan_name, initial_investment, monthly_return, annual_return, net_annual_return, slots, (err) => {
    if (err) {
      return res.status(500).json({ message: 'Erro ao adicionar plano de investimento', error: err.message });
    }
    res.status(201).json({ message: 'Plano adicionado com sucesso!' });
  });
});

// Rota para realizar um investimento
app.post('/invest', (req, res) => {
  const { plan_name, amount, investor_address } = req.body;

  getPlan(plan_name, (err, plan) => {
    if (err) {
      return res.status(500).json({ message: 'Erro ao buscar plano de investimento', error: err.message });
    }
    if (!plan) {
      return res.status(404).json({ message: 'Plano de investimento não encontrado' });
    }

    // Lógica para processar o investimento pode ser adicionada aqui

    res.status(200).json({ message: 'Investimento realizado com sucesso!' });
  });
});

// Rota para autenticar uma mensagem
app.post('/authenticate-message', (req, res) => {
  const { message_hash } = req.body;

  // Simula a lógica de autenticação de mensagem
  res.status(200).json({ message: 'Mensagem autenticada com sucesso!' });
});

// Inicia o servidor
app.listen(port, () => {
  console.log(`Servidor rodando na porta ${port}`);
});
