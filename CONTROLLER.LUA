local lapis = require("lapis")
local sqlite = require("lapis.db")
local app = lapis.Application()

-- Configuração do banco de dados
local db = sqlite.connect{
    driver = "sqlite3",
    database = ":memory:"  -- Usa banco de dados em memória para simplicidade
}

-- Criação da tabela de planos de investimento
db:query[[
    CREATE TABLE investment_plans (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        plan_name TEXT NOT NULL UNIQUE,
        initial_investment INTEGER NOT NULL,
        monthly_return INTEGER NOT NULL,
        annual_return INTEGER NOT NULL,
        net_annual_return INTEGER NOT NULL,
        slots INTEGER NOT NULL
    )
]]

-- Função para adicionar um plano de investimento
local function add_plan(planName, initialInvestment, monthlyReturn, annualReturn, netAnnualReturn, slots)
    local result, err = db:query[[
        INSERT INTO investment_plans (plan_name, initial_investment, monthly_return, annual_return, net_annual_return, slots)
        VALUES (?, ?, ?, ?, ?, ?)
    ]]:execute(planName, initialInvestment, monthlyReturn, annualReturn, netAnnualReturn, slots)
    return result, err
end

-- Função para obter um plano de investimento
local function get_plan(planName)
    return db:query[[
        SELECT * FROM investment_plans WHERE plan_name = ?
    ]]:fetch(planName)
end

-- Controlador
app:post("/add-plan", function(self)
    local planName = self.params.plan_name
    local initialInvestment = tonumber(self.params.initial_investment)
    local monthlyReturn = tonumber(self.params.monthly_return)
    local annualReturn = tonumber(self.params.annual_return)
    local netAnnualReturn = tonumber(self.params.net_annual_return)
    local slots = tonumber(self.params.slots)
    
    local success, err = add_plan(planName, initialInvestment, monthlyReturn, annualReturn, netAnnualReturn, slots)
    if not success then
        return { status = 500, json = { message = "Erro ao adicionar plano de investimento", error = err } }
    end

    return { status = 201, json = { message = "Plano adicionado com sucesso!" } }
end)

app:post("/invest", function(self)
    local planName = self.params.plan_name
    local amount = tonumber(self.params.amount)
    local investorAddress = self.params.investor_address

    local plan = get_plan(planName)
    if not plan then
        return { status = 404, json = { message = "Plano de investimento não encontrado" } }
    end

    -- Lógica para processar o investimento pode ser adicionada aqui

    return { status = 200, json = { message = "Investimento realizado com sucesso!" } }
end)

app:post("/authenticate-message", function(self)
    local messageHash = self.params.message_hash

    -- Simula a lógica de autenticação de mensagem
    return { status = 200, json = { message = "Mensagem autenticada com sucesso!" } }
end)

-- Configuração do servidor
local port = os.getenv("PORT") or 8080
app:run({ port = port })
