#include <mysql/mysql.h>
#include <iostream>

int main()
{
    const char *host = "localhost";
    const char *user = "root";
    const char *password = " ";
    const char *database = "basededatos";

    MYSQL *conn;
    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, host, user, password, database, 0, NULL, 0))
    {
        std::cerr << "Error al conectar a la base de datos: " << mysql_error(conn) << std::endl;
        return 1;
    }

    const char *query = "SELECT * FROM tabla";
    if (mysql_query(conn, query))
    {
        std::cerr << "Error al ejecutar la consulta: " << mysql_error(conn) << std::endl;
        return 1;
    }

    MYSQL_RES *res;
    res = mysql_store_result(conn);
    if (!res)
    {
        std::cerr << "Error al obtener los resultados: " << mysql_error(conn) << std::endl;
        return 1;
    }

    MYSQL_ROW row;
    while ((row = mysql_fetch_row(res)))
    {
        std::cout << row[0] << " " << row[1] << std::endl;
    }

    mysql_close(conn);
    return 0;
}