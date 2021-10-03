#ifndef SQL_H
#define SQL_H

namespace SQL {
    inline static int count = 0;
    inline static char *path = "D://123//%1.txt";
}

namespace SQL_REC {
    inline const char *insertUsers = "INSERT INTO Users (user_name, "
                                                        "password, "
                                                        "first_name, "
                                                        "last_name, "
                                                        "second_name, "
                                                        "sex, "
                                                        "date_of_birth, "
                                                        "email, "
                                                        "registration_date) "
                                               "VALUES (:user_name, "
                                                        ":password, "
                                                        ":first_name, "
                                                        ":last_name, "
                                                        ":second_name, "
                                                        ":sex, "
                                                        ":date_of_birth, "
                                                        ":email, "
                                                        ":registration_date);";

    inline const char *updateUsers = "UPDATE Users "
                                          "SET user_name = :user_name, "
                                              "password = :password, "
                                              "first_name = :first_name, "
                                              "last_name = :last_name, "
                                              "second_name = :second_name, "
                                              "date_of_birth = :date_of_birth, "
                                              "email = :email, "
                                              "photo = :photo "
                                        "WHERE id = :id;";

    inline const char *updateBalance = "UPDATE Баланс "
                                            "SET сумма_рубль = :rub, "
                                                "сумма_доллар = :dollar, "
                                                "сумма_евро = :euro "
                                          "WHERE id_клиента = :idUser;";

    inline const char *insertOperation = "INSERT INTO Опреации (ВидОпер, "
                                                              "ДатаОпер, "
                                                              "НомДог, "
                                                              "КодВалют, "
                                                              "СуммаВалют) "
                                                      "VALUES (:typeOfOperation, "
                                                              ":dateOperation, "
                                                              ":contractNumber, "
                                                              ":idCurrency, "
                                                              ":money);";

    inline const char *isertSession = "INSERT INTO Сессии (ДатаСессии, "
                                                          "КодСотруд) "
                                                  "VALUES (:date, "
                                                          ":idEmployee);";

    inline const char *selectMyOperaton = "SELECT DISTINCT O.ДатаОпер, "
                                                        "O.ВидОпер, "
                                                        "Cur.Валюта, "
                                                        "Cur.Флаг, "
                                                        "O.КодВалют, "
                                                        "O.СуммаВалют, "
                                                        "Sot.Сотрудник "
                                                    "FROM Опреации O INNER JOIN Договоры C ON O.НомДог = C.НомДог INNER JOIN Users ON Users.id = C.КодКлиент "
                                                    "INNER JOIN Валюты Cur ON O.КодВалют = Cur.КодВалют "
                                                    "INNER JOIN Сессии Ses ON O.ДатаОпер = Ses.ДатаСессии INNER JOIN [Курсы валют] ExRates ON O.КодВалют = ExRates.КодВалют "
                                                    "INNER JOIN Сотрудники Sot ON Ses.КодСотруд = Sot.КодСотруд "
                                                    "WHERE Users.id = :id "
                                                    "ORDER BY O.ДатаОпер DESC;";

}

#endif // SQL_H
