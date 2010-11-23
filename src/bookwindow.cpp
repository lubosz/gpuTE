#include "bookwindow.h"
#include "bookwrapper.h"
#include "initdb.h"
#include <iostream>

#include <QtSql>

#include <grantlee_core.h>

BookWindow::BookWindow()
{

    if (!QSqlDatabase::drivers().contains("QSQLITE"))
        qDebug() << (this, "Unable to load database", "This demo needs the SQLITE driver");

    // initialize the database
    QSqlError err = initDb();
    if (err.type() != QSqlError::NoError) {
        showError(err);
        return;
    }

    // Create the data model
    model = new QSqlRelationalTableModel();
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setTable("books");

    // Rememeber the indexes of the columns
    authorIdx = model->fieldIndex("author");
    genreIdx = model->fieldIndex("genre");

    // Set the relations to the other database tables
    model->setRelation(authorIdx, QSqlRelation("authors", "id", "name"));
    model->setRelation(genreIdx, QSqlRelation("genres", "id", "name"));

    // Populate the model
    if (!model->select()) {
        showError(model->lastError());
        return;
    }

    m_engine = new Grantlee::Engine();
    Grantlee::FileSystemTemplateLoader::Ptr loader = Grantlee::FileSystemTemplateLoader::Ptr( new Grantlee::FileSystemTemplateLoader() );
    loader->setTemplateDirs( QStringList() << GRANTLEE_TEMPLATE_PATH );
    m_engine->addTemplateLoader(loader);
}

void BookWindow::showError(const QSqlError &err)
{
    qDebug() << (this, "Unable to initialize Database",
                "Error initializing database: " + err.text());
}

void BookWindow::renderBooks()
{
    int rows = model->rowCount();
    QVariantHash mapping;
    QVariantList bookList;
    for (int row = 0; row < rows; ++row)
    {
      QString title = model->index(row, 1).data().toString();
      QString author = model->index(row, 2).data().toString();
      QString genre = model->index(row, 3).data().toString();
      int rating = model->index(row, 5).data().toInt();
      QObject *book = new BookWrapper(author, title, genre, rating);
      QVariant var = QVariant::fromValue(book);
      bookList.append(var);
    }
    mapping.insert("books", bookList);

    QString themeName = "simple";

    Grantlee::Context c(mapping);

    Grantlee::Template t = m_engine->loadByName( themeName + ".html" );
    if (!t)
    {
      qDebug() << (this, "Unable to load template",
                QString( "Error loading template: %1" ).arg( themeName + ".html" ) );
      return;
    }

    if ( t->error() )
    {
      qDebug() << (this, "Unable to load template",
                QString( "Error loading template: %1" ).arg( t->errorString() ) );
      return;
    }

    QString content = t->render(&c);

    if ( t->error() )
    {
      qDebug() << (this, "Unable render template",
                QString( "Error rendering template: %1" ).arg( t->errorString() ) );
      return;
    }

    std::cout << qPrintable(content);

}
