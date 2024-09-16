-- Estrutura de cache para armazenar dados de pesquisa
Cache = {}
Cache.__index = Cache

-- Função para criar um novo cache com um tamanho máximo
function Cache:new(max_size)
    local obj = {
        data = {},          -- tabela para armazenar os dados
        keys = {},          -- lista de chaves para controlar a ordem de inserção
        max_size = max_size -- limite máximo do cache
    }
    setmetatable(obj, Cache)
    return obj
end

-- Função para adicionar dados ao cache
function Cache:add(key, value)
    -- Se a chave já existir, atualize o valor
    if self.data[key] then
        self.data[key] = value
        print("Valor atualizado no cache para a chave: " .. key)
    else
        -- Se o cache atingir o tamanho máximo, remove o item mais antigo
        if #self.keys >= self.max_size then
            local old_key = table.remove(self.keys, 1)
            self.data[old_key] = nil
            print("Removido do cache (LRU): " .. old_key)
        end
        -- Adiciona o novo item ao cache
        table.insert(self.keys, key)
        self.data[key] = value
        print("Novo item adicionado ao cache: " .. key)
    end
end

-- Função para buscar um item no cache
function Cache:get(key)
    if self.data[key] then
        print("Item encontrado no cache: " .. key)
        return self.data[key]
    else
        print("Item não encontrado no cache: " .. key)
        return nil
    end
end

-- Função para remover um item do cache
function Cache:remove(key)
    for i, k in ipairs(self.keys) do
        if k == key then
            table.remove(self.keys, i)
            self.data[key] = nil
            print("Item removido do cache: " .. key)
            return
        end
    end
    print("Item não encontrado no cache para remoção: " .. key)
end

-- Função para listar todos os itens no cache
function Cache:listAll()
    print("Listando todos os itens no cache:")
    for _, key in ipairs(self.keys) do
        print(key .. ": " .. self.data[key])
    end
end

-- Otimizador Seal Learning
SealLearning = {}
SealLearning.__index = SealLearning

function SealLearning:new()
    local obj = { learningData = {} } -- Armazena dados de aprendizado de pesquisa
    setmetatable(obj, SealLearning)
    return obj
end

-- Função para otimizar o cache com IA (exemplo simples de aprendizado)
function SealLearning:optimize(cache)
    print("Otimizando cache com IA Seal Learning...")
    -- IA ajusta as prioridades de pesquisa, reordenando o cache
    -- Aqui aplicamos um exemplo de ajuste: reorganizando com base na frequência de uso
    local optimizedData = {}
    local frequencyTable = {}

    -- Conta as ocorrências de acesso aos dados
    for _, key in ipairs(cache.keys) do
        frequencyTable[key] = (frequencyTable[key] or 0) + 1
    end

    -- Reordena os dados no cache com base na frequência
    for key, _ in pairs(frequencyTable) do
        table.insert(optimizedData, key)
    end

    -- Atualiza o cache com a nova ordem de dados otimizados
    cache.keys = optimizedData
    print("Cache otimizado com base na frequência de acesso.")
end

-- Exemplo de como o NSC Token pode ser integrado para monitorar o cache
NSCToken = {}
NSCToken.__index = NSCToken

function NSCToken:new()
    local obj = { transactions = {} }
    setmetatable(obj, NSCToken)
    return obj
end

-- Função para registrar transações associadas ao cache
function NSCToken:trackTransaction(key, action)
    table.insert(self.transactions, {key = key, action = action})
    print("Transação registrada para: " .. key .. " com ação: " .. action)
end

-- Exemplo de uso das funções definidas
function main()
    -- Criação de um cache com tamanho máximo 3
    local myCache = Cache:new(3)
    local optimizer = SealLearning:new()
    local tokenTracker = NSCToken:new()

    -- Adicionar dados ao cache
    myCache:add("Pesquisa1", "Resultado1")
    tokenTracker:trackTransaction("Pesquisa1", "add")

    myCache:add("Pesquisa2", "Resultado2")
    tokenTracker:trackTransaction("Pesquisa2", "add")

    myCache:add("Pesquisa3", "Resultado3")
    tokenTracker:trackTransaction("Pesquisa3", "add")

    -- Listar todos os itens no cache
    myCache:listAll()

    -- Buscar um item
    myCache:get("Pesquisa1")

    -- Adicionar um novo item que vai causar a remoção do mais antigo (LRU)
    myCache:add("Pesquisa4", "Resultado4")
    tokenTracker:trackTransaction("Pesquisa4", "add")

    -- Listar todos os itens após a remoção
    myCache:listAll()

    -- Otimizar o cache com IA (Seal Learning)
    optimizer:optimize(myCache)

    -- Listar itens após otimização
    myCache:listAll()
end

main()
