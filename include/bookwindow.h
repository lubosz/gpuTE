#pragma once

#include <QtSql>

namespace Grantlee
{
class Engine;
}

class BookWindow
{
public:
    BookWindow();

    void renderBooks();

private:
    void showError(const QSqlError &err);
    QSqlRelationalTableModel *model;
    int authorIdx, genreIdx;
    Grantlee::Engine *m_engine;
};

