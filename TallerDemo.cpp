#include <iostream>
#include <windows.h>
#include <sql.h>
#include <sqlext.h>

int main() {
    // Variables para manejar la conexión
    SQLHENV hEnv;
    SQLHDBC hDbc;
    SQLHSTMT hStmt;

    // Inicializar el entorno de ODBC
    SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv);
    SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0);

    // Establecer la conexión
    SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc);
    SQLCHAR* connectionString = (SQLCHAR*)"DRIVER={MySQL ODBC 8.0 Unicode Driver}; SERVER=localhost; DATABASE=ODBCTest; UID=root; PWD=DiegotsSystems03#; OPTION=3;";
    SQLRETURN retcode = SQLDriverConnectA(hDbc, NULL, connectionString, SQL_NTS, NULL, 0, NULL, SQL_DRIVER_NOPROMPT);

    if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
        std::cout << "Conexión establecida correctamente." << std::endl;

        // Ejecutar una consulta
        SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);
        SQLCHAR* query = (SQLCHAR*)"SELECT * FROM ejemplo";
        retcode = SQLExecDirectA(hStmt, query, SQL_NTS);

        if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
            // Procesar resultados
            SQLCHAR name[255];
            SQLLEN indicator;
            while (SQLFetch(hStmt) == SQL_SUCCESS) {
                SQLGetData(hStmt, 2, SQL_C_CHAR, name, 255, &indicator); // Columna 2 (nombre)
                std::cout << "Nombre: " << name << std::endl;
            }
        }
        else {
            std::cerr << "Error al ejecutar la consulta." << std::endl;
        }

        // Liberar recursos
        SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
        SQLDisconnect(hDbc);
    }
    else {
        std::cerr << "Error al establecer la conexión." << std::endl;
    }

    // Liberar recursos
    SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
    SQLFreeHandle(SQL_HANDLE_ENV, hEnv);

    return 0;
}
