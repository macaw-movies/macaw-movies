/* Copyright (C) 2014 Macaw-Movies
 * (Olivier CHURLAUD, Sébastien TOUZÉ)
 *
 * This file is part of Macaw-Movies.
 *
 * Macaw-Movies is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Macaw-Movies is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Macaw-Movies.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "MetadataFetcherDialog.h"
#include "ui_MetadataFetcherDialog.h"

MetadataFetcherDialog::MetadataFetcherDialog(Movie movie, QList<Movie> moviesPropositionList, QWidget *parent):
    QDialog(parent),
    m_ui(new Ui::MetadataFetcherDialog)
{
    m_app = qobject_cast<Application *>(qApp);
    m_app->debug("[MetadataFetcherDialog] Constructor called");
    m_ui->setupUi(this);

    m_ui->lineEdit->setText(movie.getTitle());
    m_ui->moviePathLabel->setText(movie.getFilePath());
    foreach (Movie l_movieProposition, moviesPropositionList)
    {
        QListWidgetItem *l_item = new QListWidgetItem;
        QString l_textItem = l_movieProposition.getTitle()
                + " [" + QString::number(l_movieProposition.getReleaseDate().year())
                + "]";
        l_item->setText(l_textItem);
        l_item->setData(Macaw::ObjectId, l_movieProposition.getId());
        m_ui->listWidget->addItem(l_item);
    }
}

MetadataFetcherDialog::~MetadataFetcherDialog()
{
    delete m_ui;
}


void MetadataFetcherDialog::on_buttonBox_accepted()
{
    if (m_ui->listWidget->selectedItems().count() == 0)
    {
        QMessageBox::warning(this, "Warning", "You must select a movie!");
    }
    else
    {
        int tmdbID = m_ui->listWidget->selectedItems().at(0)->data(Macaw::ObjectId).toInt();
        emit(selectedMovie(tmdbID));
        this->accept();
    }
}

void MetadataFetcherDialog::on_listWidget_doubleClicked(const QModelIndex &index)
{
    int tmdbID = index.data(Macaw::ObjectId).toInt();
    emit(selectedMovie(tmdbID));
    this->accept();
}
