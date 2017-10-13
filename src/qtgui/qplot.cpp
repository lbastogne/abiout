/**
 * @file src/./qplot.cpp
 *
 * @brief 
 *
 * @author Jordan Bieder <jordan.bieder@cea.fr>
 *
 * @copyright Copyright 2017 Jordan Bieder
 *
 * This file is part of AbiOut.
 *
 * AbiOut is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * AbiOut is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with AbiOut.  If not, see <http://www.gnu.org/licenses/>.
 */


#include "qtgui/qplot.hpp"
#include "base/exception.hpp"

const QColor QPlot::qcolor[] = { Qt::black, Qt::red, Qt::green, Qt::blue, Qt::magenta, Qt::cyan, Qt::darkRed, Qt::darkGreen, Qt::darkYellow };

//
QPlot::QPlot(QWidget *parent) : QMainWindow(parent), Graph(),
  _plot(new QCustomPlot(this)),
  _titleElement(new QCPTextElement(_plot, QString::fromStdString(_title), QFont("Helvetica", 12, QFont::Bold))),
  _save(nullptr),
  _autozoom(nullptr),
  _arrowsItems()
{
  this->resize(640,480);
  //_plot->resize(640,480);
  this->setCentralWidget(_plot);
  this->createStatusBar();
  this->setWindowTitle(QString::fromStdString("Agate Plot"));
  _plot->setAutoAddPlottableToLegend(false);
  _plot->plotLayout()->insertRow(0);
  _plot->plotLayout()->addElement(0, 0, _titleElement);
  _plot->setOpenGl(false);
  _plot->setInteractions(QCP::Interaction::iRangeDrag|QCP::Interaction::iRangeZoom);
  //_plot->setRangeZoomAxis(_plot->xAxis,_plot->yAxis);
  connect(_plot->xAxis, SIGNAL(rangeChanged(QCPRange)), _plot->xAxis2, SLOT(setRange(QCPRange)));
  connect(_plot->yAxis, SIGNAL(rangeChanged(QCPRange)), _plot->yAxis2, SLOT(setRange(QCPRange)));
  connect(_plot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePressed(QMouseEvent*)));

  _plot->selectionRect()->setPen(QPen(QColor(50,50,50,200),2,Qt::SolidLine));
  _plot->selectionRect()->setBrush(QBrush(QColor(125,125,125,50)));
  this->setFocusPolicy(Qt::StrongFocus);

  QToolBar *toolBar = this->addToolBar("Agate Plot");
  toolBar->setMovable(false);
  toolBar->setFloatable(false);

  _save = new QAction(QIcon(":/write.png"),QString("Export to PDF"),toolBar);
  _save->setShortcut(QKeySequence::Save);
  _save->setStatusTip("Export plot to PDF");

  _autozoom = new QAction(QIcon(":/autozoom.png"),QString("Auto zoom"),toolBar);
  _autozoom->setShortcut(QKeySequence("u"));
  _autozoom->setStatusTip("Auto zoom");

  toolBar->addAction(_save);
  toolBar->addAction(_autozoom);
  connect(_save,SIGNAL(triggered()),this,SLOT(save()));
  connect(_autozoom,SIGNAL(triggered()),this,SLOT(autozoom()));
}

//
QPlot::~QPlot() {
  ;
}

void QPlot::plot(const std::vector<double> &x, const std::list<std::vector<double>> &y, const std::list<std::string> &labels, const std::vector<short> &colors){
  this->clean();
  this->show();
  auto label = labels.begin();
  auto yp = y.begin();
  int autocolor = 1;
  bool addedLabel = false;
  for ( unsigned p = 0 ; p < y.size() ; ++p) {
    _plot->addGraph();
    auto graph = _plot->graph(p);
    if ( p < colors.size() ) {
      graph->setPen(QPen(qcolor[colors[p] < 8 ? colors[p] : autocolor++]));
    }
    else {
      graph->setPen(QPen(qcolor[autocolor++]));
    }
    if ( autocolor >= 8 ) autocolor = 0;


    if ( p < labels.size() ) {
      if ( !label->empty() ) {
        graph->setName(QString::fromStdString(*label));
        graph->addToLegend();
        addedLabel = true;
      }
      ++label;
    }
    graph->setData(QVector<double>::fromStdVector(x),QVector<double>::fromStdVector(*yp));
    ++yp;
  }
  _plot->rescaleAxes(true);
  _plot->xAxis2->setVisible(true);
  _plot->xAxis2->setTickLabels(false);
  _plot->yAxis2->setVisible(true);
  _plot->yAxis2->setTickLabels(false);
  _plot->xAxis->setLabel(QString::fromStdString(_xlabel));
  _plot->yAxis->setLabel(QString::fromStdString(_ylabel));
  _plot->legend->setVisible(addedLabel);
  _titleElement->setText(QString::fromStdString(_title));
  this->addCustom();
  _plot->replot();
}

void QPlot::plot(const std::list< std::pair< std::vector<double>,std::vector<double> > > &xy, const std::list<std::string> &labels, const std::vector<short> &colors) {
  this->clean();
  this->show();
  auto label = labels.begin();
  auto xyp = xy.begin();
  int autocolor = 1;
  bool addedLabel = false;
  for ( unsigned p = 0 ; p < xy.size() ; ++p) {
    QCPCurve *newCurve = new QCPCurve(_plot->xAxis, _plot->yAxis);
    if ( p < colors.size() ) {
      newCurve->setPen(QPen(qcolor[colors[p] < 8 ? colors[p] : autocolor++]));
    }
    else {
      newCurve->setPen(QPen(qcolor[autocolor++]));
    }
    if ( autocolor >= 8 ) autocolor = 0;

    if ( p < labels.size() ) {
      if ( !label->empty() ) {
        newCurve->setName(QString::fromStdString(*label));
        newCurve->addToLegend();
        addedLabel = true;
      }
      ++label;
    }
    newCurve->setData(QVector<double>::fromStdVector(xyp->first),QVector<double>::fromStdVector(xyp->second));
    ++xyp;
  }
  _plot->rescaleAxes(true);
  _plot->xAxis2->setVisible(true);
  _plot->xAxis2->setTickLabels(false);
  _plot->yAxis2->setVisible(true);
  _plot->yAxis2->setTickLabels(false);
  _plot->xAxis->setLabel(QString::fromStdString(_xlabel));
  _plot->yAxis->setLabel(QString::fromStdString(_ylabel));
  _plot->legend->setVisible(addedLabel);
  _titleElement->setText(QString::fromStdString(_title));
  this->addCustom();
  _plot->replot();
}

void QPlot::save(std::string filename){
  _plot->savePdf(QString::fromStdString(filename+".pdf"),0,0,QCP::epNoCosmetic);
}

void QPlot::clean(){
  _plot->clearPlottables();
  for ( auto a : _arrowsItems ) {
    _plot->removeItem(a);
  }
  _arrowsItems.clear();
  _plot->xAxis->setTicker(QSharedPointer<QCPAxisTicker>(new QCPAxisTicker));
  _plot->yAxis->setTicker(QSharedPointer<QCPAxisTicker>(new QCPAxisTicker));
}

void QPlot::dump(std::ostream& out, std::string& plotname) const {
  (void) out;
  (void) plotname;
}

void QPlot::resizeEvent(QResizeEvent * event) {
  QMainWindow::resizeEvent(event);
  //_plot->resize(event->size());
  _plot->replot();
}

void QPlot::setWinTitle(std::string title) { 
  _winTitle = title+" - QAgate";
  this->setWindowTitle(QString::fromStdString(_winTitle));
}

void QPlot::createStatusBar() {
  this->statusBar()->showMessage("");
  connect(_plot,SIGNAL(mouseMove(QMouseEvent*)),this,SLOT(updateStatusBar(QMouseEvent*)));
}

void QPlot::updateStatusBar(QMouseEvent *event) {
  double x = _plot->xAxis->pixelToCoord(event->pos().x());
  double y = _plot->yAxis->pixelToCoord(event->pos().y());
  QString info = "x=" + QString::number(x) + " y=" + QString::number(y);
  this->statusBar()->showMessage(info);
}

void QPlot::mousePressed(QMouseEvent *event) {
  if ( event->button() == Qt::MouseButton::RightButton ) {
    _plot->setSelectionRectMode(QCP::SelectionRectMode::srmZoom);
  }
  else if ( event->button() == Qt::MouseButton::LeftButton ) {
    _plot->setSelectionRectMode(QCP::SelectionRectMode::srmNone);
  }
}

void QPlot::autozoom(){
  _plot->rescaleAxes(true);
  _plot->replot();
}

void QPlot::save(){
  auto name = QFileDialog::getSaveFileName(this, "Save File", "", "PDF (*.pdf)");
  if ( !name.isEmpty() ) {
    if ( !name.endsWith(".pdf",Qt::CaseInsensitive) )
      name.append(".pdf");
    _plot->savePdf(name,0,0,QCP::epNoCosmetic);
  }
}

void QPlot::addCustom() {
  if ( _xrange.set )
    _plot->xAxis->setRange(_xrange.min,_xrange.max);

  if ( _yrange.set )
    _plot->yAxis->setRange(_yrange.min,_yrange.max);

  if ( _xtics.size() > 0 ) {
    QSharedPointer<QCPAxisTickerText> xtickers(new QCPAxisTickerText);
    _plot->xAxis->setTicker(xtickers);
    for ( auto t : _xtics )
      xtickers->addTick(t.position,QString::fromStdString(t.label));
  }

  if ( _ytics.size() > 0 ) {
    QSharedPointer<QCPAxisTickerText> ytickers(new QCPAxisTickerText);
    _plot->yAxis->setTicker(ytickers);
    for ( auto t : _ytics )
      ytickers->addTick(t.position,QString::fromStdString(t.label));
  }

  if ( _arrows.size() > 0 ) {
    for ( auto a : _arrows ) {
      QCPItemLine *arrow = new QCPItemLine(_plot);
      _arrowsItems.push_back(arrow);
      arrow->start->setCoords(a.x1,a.y1);
      arrow->end->setCoords(a.x2,a.y2);
      arrow->setHead(a.head ? QCPLineEnding::esSpikeArrow : QCPLineEnding::esNone );
    }
  }
}
