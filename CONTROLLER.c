#include <stdio.h>
#include <sqlite3.h>
#include "libxlsxwriter.h"  // Se estiver usando libxlsxwriter

// Estrutura para armazenar os dados dos investidores
typedef struct {
    int id;
    char name[100];
    char email[100];
    char phone_number[20];
} Investor;

// Estrutura para armazenar os dados dos ativos
typedef struct {
    int id;
    char asset_name[100];
    char asset_type[50];
    int total_slots;
    double annual_return;
} Asset;

// Estrutura para armazenar o investimento
typedef struct {
    int id;
    int investor_id;
    int asset_id;
    double invested_amount;
} Investment;
// Função para inserir investidores
void insert_investor(sqlite3 *db, Investor investor) {
    char *err_msg = 0;
    char sql[256];

    sprintf(sql, "INSERT INTO Investors (name, email, phone_number) VALUES ('%s', '%s', '%s');",
            investor.name, investor.email, investor.phone_number);

    int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro ao inserir investidor: %s\n", err_msg);
        sqlite3_free(err_msg);
    } else {
        printf("Investidor inserido com sucesso!\n");
    }
}

// Função para inserir ativos
void insert_asset(sqlite3 *db, Asset asset) {
    char *err_msg = 0;
    char sql[256];

    sprintf(sql, "INSERT INTO Assets (asset_name, asset_type, total_slots, annual_return) VALUES ('%s', '%s', %d, %f);",
            asset.asset_name, asset.asset_type, asset.total_slots, asset.annual_return);

    int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro ao inserir ativo: %s\n", err_msg);
        sqlite3_free(err_msg);
    } else {
        printf("Ativo inserido com sucesso!\n");
    }
}

// Função para inserir investimentos
void insert_investment(sqlite3 *db, Investment investment) {
    char *err_msg = 0;
    char sql[256];

    sprintf(sql, "INSERT INTO Investments (investor_id, asset_id, invested_amount) VALUES (%d, %d, %f);",
            investment.investor_id, investment.asset_id, investment.invested_amount);

    int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro ao inserir investimento: %s\n", err_msg);
        sqlite3_free(err_msg);
    } else {
        printf("Investimento inserido com sucesso!\n");
    }
}
// Função para ler dados de Excel usando libxlsxwriter
void read_excel_data(const char *file_path) {
    lxw_workbook  *workbook  = workbook_new(file_path);
    lxw_worksheet *worksheet = workbook_add_worksheet(workbook, NULL);

    // Lógica para ler dados das planilhas
    // Depois de ler, chame as funções de inserção no banco de dados

    workbook_close(workbook);
}
// Função para inicializar o banco de dados e criar tabelas
void initialize_database(sqlite3 **db) {
    int rc = sqlite3_open("investments.db", db);

    if (rc) {
        fprintf(stderr, "Erro ao abrir o banco de dados: %s\n", sqlite3_errmsg(*db));
        return;
    }

    char *err_msg = 0;

    // Criação das tabelas
    const char *sql_investors = "CREATE TABLE IF NOT EXISTS Investors ("
                                "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                "name TEXT NOT NULL,"
                                "email TEXT NOT NULL,"
                                "phone_number TEXT NOT NULL);";

    const char *sql_assets = "CREATE TABLE IF NOT EXISTS Assets ("
                             "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                             "asset_name TEXT NOT NULL,"
                             "asset_type TEXT NOT NULL,"
                             "total_slots INTEGER NOT NULL,"
                             "annual_return REAL NOT NULL);";

    const char *sql_investments = "CREATE TABLE IF NOT EXISTS Investments ("
                                  "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                  "investor_id INTEGER,"
                                  "asset_id INTEGER,"
                                  "invested_amount REAL,"
                                  "FOREIGN KEY(investor_id) REFERENCES Investors(id),"
                                  "FOREIGN KEY(asset_id) REFERENCES Assets(id));";

    rc = sqlite3_exec(*db, sql_investors, 0, 0, &err_msg);
    rc |= sqlite3_exec(*db, sql_assets, 0, 0, &err_msg);
    rc |= sqlite3_exec(*db, sql_investments, 0, 0, &err_msg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro ao criar tabelas: %s\n", err_msg);
        sqlite3_free(err_msg);
    } else {
        printf("Banco de dados inicializado com sucesso!\n");
    }
}
