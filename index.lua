-- Requer o módulo de SQL (exemplo com SQLite)
local sqlite3 = require("sqlite3")
local csv = require("csv")  -- Para gerar relatórios em formato CSV

-- Conectando ao banco de dados de ativos financeiros
local db = sqlite3.open('ativos_financeiros.db')

-- Função para criar a tabela de controle de ativos financeiros
function criar_tabela()
    local query = [[
        CREATE TABLE IF NOT EXISTS ativos (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            nome TEXT,
            valor REAL,
            tipo TEXT,
            data_aquisicao TEXT,
            descricao TEXT
        );
    ]]
    db:exec(query)
    print("Tabela de ativos financeiros criada com sucesso.")
end

-- Função para adicionar um ativo financeiro
function adicionar_ativo(nome, valor, tipo, data_aquisicao, descricao)
    local stmt = db:prepare("INSERT INTO ativos (nome, valor, tipo, data_aquisicao, descricao) VALUES (?, ?, ?, ?, ?)")
    stmt:bind_values(nome, valor, tipo, data_aquisicao, descricao)
    stmt:step()
    stmt:finalize()
    print("Ativo adicionado com sucesso.")
end

-- Função para atualizar um ativo financeiro
function atualizar_ativo(id, nome, valor, tipo, data_aquisicao, descricao)
    local stmt = db:prepare("UPDATE ativos SET nome = ?, valor = ?, tipo = ?, data_aquisicao = ?, descricao = ? WHERE id = ?")
    stmt:bind_values(nome, valor, tipo, data_aquisicao, descricao, id)
    stmt:step()
    stmt:finalize()
    print("Ativo atualizado com sucesso.")
end

-- Função para visualizar todos os ativos financeiros
function visualizar_ativos()
    for row in db:nrows("SELECT * FROM ativos") do
        print(string.format("ID: %d, Nome: %s, Valor: %.2f, Tipo: %s, Data: %s, Descrição: %s", row.id, row.nome, row.valor, row.tipo, row.data_aquisicao, row.descricao))
    end
end

-- Função para excluir um ativo financeiro
function excluir_ativo(id)
    local stmt = db:prepare("DELETE FROM ativos WHERE id = ?")
    stmt:bind_values(id)
    stmt:step()
    stmt:finalize()
    print("Ativo excluído com sucesso.")
end

-- Função para gerar o relatório de ativos financeiros em formato CSV
function gerar_relatorio_csv(caminho_arquivo)
    local file = io.open(caminho_arquivo, "w")
    file:write("ID,Nome,Valor,Tipo,Data de Aquisição,Descrição\n")
    for row in db:nrows("SELECT * FROM ativos") do
        file:write(string.format("%d,%s,%.2f,%s,%s,%s\n", row.id, row.nome, row.valor, row.tipo, row.data_aquisicao, row.descricao))
    end
    file:close()
    print("Relatório CSV gerado com sucesso em: " .. caminho_arquivo)
end

-- Mapeamento de ativos para planilha financeira
function mapear_ativos_para_planilha()
    local caminho_arquivo = "ativos_financeiros.csv"
    gerar_relatorio_csv(caminho_arquivo)
end

-- Inicialização e controle dos ativos
function inicializar_sistema()
    criar_tabela()

    -- Exemplos de operação
    adicionar_ativo("Imóvel Comercial", 1000000, "Real Estate", "2024-01-10", "Loja no centro da cidade")
    adicionar_ativo("Ações da Empresa X", 50000, "Ações", "2024-02-15", "Ações compradas na bolsa de valores")

    print("\nVisualizando todos os ativos financeiros:")
    visualizar_ativos()

    print("\nGerando o relatório CSV dos ativos:")
    mapear_ativos_para_planilha()
end

-- Fechar a conexão com o banco de dados ao finalizar o script
function finalizar_sistema()
    db:close()
end

-- Iniciando o sistema de controle de ativos
inicializar_sistema()
finalizar_sistema()
