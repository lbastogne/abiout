/**
 * @file include/./qplot.hpp
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


#ifndef QPLOT_HPP
#define QPLOT_HPP

#ifdef _WIN32
#include "base/win32.hpp"
#endif

#ifdef HAVE_CONFIG_H
#include "config.h"
#undef HAVE_CONFIG_H
#endif

#  ifdef __GNUC__
#    if __GNUC__ >= 4
#      if __GNUC_MINOR__ >= 6
#        pragma GCC diagnostic push
#        pragma GCC diagnostic ignored "-Weffc++"
#      endif
#    endif
#    pragma GCC system_header
#  endif
#include <QDialog>
#include <QColor>
#include "plot/graph.hpp"
#include "qtgui/qcustomplot.h"

/** 
 *
 */
class QPlot : public QDialog, public Graph {
  Q_OBJECT

  private :
    QCustomPlot *_plot;
    QCPTextElement *_titleElement;

  protected :
    //static const QColor qcolor[] = {{ Qt::black, Qt::red, Qt::green, Qt::blue, Qt::magenta, Qt::cyan, Qt::darkRed, Qt::darkGreen, Qt::darkYellow }};
    static const QColor qcolor[];

  public :

    /**
     * Constructor.
     */
    QPlot(QWidget *parent);

    /**
     * Destructor.
     */
    virtual ~QPlot();

    /** 
     * Plot several quantities on the screen
     * @param x The x quantity
     * @param y A vector with several y quantites to plot
     * @param labels The labels corresponding to the y quantities.
     */
    virtual void plot(std::vector<double> x, std::list<std::vector<double>> y, std::list<std::string> labels, std::vector<short> colors);

    /** 
     * Plot several quantities on the screen
     * @param xy A list of (x,y) pairs to plot
     * @param labels The labels corresponding to the y quantities.
     */
    virtual void plot(std::list< std::pair< std::vector<double>,std::vector<double> > > xy, std::list<std::string> labels, std::vector<short> colors);

    /**
     * Save the graph
     * @param filename Save to filename
     * */
    virtual void save(std::string filename);

    /**
     * Clean everything
     */
    virtual void clean();

    /**
     * Add custom command depending on frontend
     * @param customlines The custom commands to add
     */
    virtual void custom(const std::string &customlines);

    /**
     * Print out the commande to plot
     * @param out ostream for output
     * @param plotname is the filename for the file that would be created when the graph is created
     * Not the script file that would be executed to creat the graph
     */
    virtual void dump(std::ostream& out, std::string& plotname) const;

    virtual void resizeEvent(QResizeEvent * event);

};

#endif  // QPLOT_HPP
