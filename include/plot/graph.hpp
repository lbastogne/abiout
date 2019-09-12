/**
 * @file include/graph.hpp
 *
 * @brief 
 *
 * @author Jordan Bieder <jordan.bieder@cea.fr>
 *
 * @copyright Copyright 2014 Jordan Bieder
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


#ifndef GRAPH_HPP
#define GRAPH_HPP

#ifdef _WIN32
#include "base/win32.hpp"
#endif

#ifdef HAVE_CONFIG_H
#include "agate.h"
#undef HAVE_CONFIG_H
#endif

#include <string>
#include <list>
#include <vector>
#include <ostream>
#include <fstream>
#include "io/configparser.hpp"
//#include "io/eigparser.hpp"

class EigParser;

/** 
 *
 */
class Graph {

  private :

  protected :

    /**
     * Structure to store ticks which are a position on one axe and a label
     */
    typedef struct tic {
      double position;   ///< Position of the new tick
      std::string label; ///< Label of the new tick
      tic() : position(0), label() {;}
    } tic;

    /**
     * Structure to store an arrow descriptor
     */
    typedef struct arrow {
      double x1; ///< Point 1 x position
      double y1; ///< Point 1 y position
      double x2; ///< Point 2 x position
      double y2; ///< Point 2 y position
      bool head; ///< True if the arrow has a head 
    } arrow;

    typedef struct range {
      double min;
      double max;
      bool set;
    } range;


    std::string _xlabel; ///< Label for x axis
    std::string _ylabel; ///< Label for y axis
    std::string _title;  ///< Title for the graph
    std::string _winTitle; ///< Title of the window if supported.
    std::vector<tic>  _xtics; ///< New ticks to display on the x axis
    std::vector<tic>  _ytics; ///< New ticks to display on the y axis
    std::vector<arrow> _arrows; ///< Arrow to display on the graph
    range _xrange;
    range _yrange;
    

  public :

    /** 
     * Type to know what to do with the plot function
     */
    enum GraphSave { NONE, PRINT, DATA };

    typedef struct Config {
      std::vector<double> x;
      std::list<std::vector<double>> y;
      std::list<std::vector<unsigned>> rgb;
      std::list<std::pair<std::vector<double>,std::vector<double>>> xy;
      std::list<std::string> labels;
      std::vector<short> colors;
      std::string filename;
      std::string xlabel;
      std::string ylabel;
      std::string title;
      GraphSave save;
      bool doSumUp;

      Config() :
        x(),
        y(),
        rgb(),
        xy(),
        labels(),
        colors(),
        filename("Untitled"),
        xlabel(),
        ylabel(),
        title("Untitled"),
        save(NONE),
        doSumUp(true) 
      {}
    } Config;

    /**
     * Constructor.
     */
    Graph();

    /**
     * Destructor.
     */
    virtual ~Graph();

    /** 
     * Plot several quantities on the screen
     * @param x The x quantity
     * @param y A vector with several y quantites to plot
     * @param labels The labels corresponding to the y quantities.
     */
    virtual void plot(const std::vector<double> &x, const std::list<std::vector<double>> &y, const std::list<std::string> &labels, const std::vector<short> &colors) = 0;

    /** 
     * Plot several quantities on the screen
     * @param xy A list of (x,y) pairs to plot
     * @param labels The labels corresponding to the y quantities.
     */
    virtual void plot(const std::list< std::pair< std::vector<double>,std::vector<double> > > &xy, const std::list<std::string> &labels, const std::vector<short> &colors) = 0;

    /** 
     * Plot several quantities on the screen
     * @param x The x quantity
     * @param y A vector with several y quantites to plot
     * @param c A vector with colors for each x coordinate
     * @param labels The labels corresponding to the y quantities.
     */
    virtual void plot(const std::vector<double> &x, const std::list<std::vector<double>> &y, const std::list<std::vector<unsigned>> &c, const std::list<std::string> &labels) = 0;

    /**
     * Save the graph
     * @param filename Save to filename
     * */
    virtual void save(std::string filename) = 0;

    /**
     * Clean everything
     */
    virtual void clean() {;}

    /**
     * Setter
     * @param lab The new value 
     */
    virtual void setXLabel(std::string lab) { _xlabel = lab; }

    /**
     * Setter
     * @param lab The new value 
     */
    virtual void setYLabel(std::string lab) { _ylabel = lab; }

    /**
     * Setter
     * @param lab The new value 
     */
    virtual void setTitle(std::string lab) { _title = lab; }

    /**
     * Setter
     * @param title the new window title
     */
    virtual void setWinTitle(std::string title) { _winTitle = title; }

    /**
     * Set the range of y axis
     * @param min minimal value
     * @param max maximal value
     */
    virtual void setXRange(double min, double max);

    /**
     * Set the range of y axis
     * @param min minimal value
     * @param max maximal value
     */
    virtual void setYRange(double min, double max);

    /**
     * add xticks
     * @param name The xtick label to use
     * @param pos the position on the x axis
     */
    virtual void addXTic(std::string name, double pos);

    /**
     * add yticks
     * @param name The xtick label to use
     * @param pos the position on the y axis
     */
    virtual void addYTic(std::string name, double pos);

    /**
     * add an arrow with or without head from first point to second one
     * @param x1 xposition of the starting point
     * @param y1 yposition of the starting point
     * @param x2 xposition of the head point
     * @param y2 yposition of the head point
     * @param head True if the arrow head is displayed
     */
    virtual void addArrow(double x1, double y1, double x2, double y2, bool head = false);

    void clearCustom();

    /**
     * Print out the commande to plot
     * @param out ostream for output
     * @param plotname is the filename for the file that would be created when the graph is created
     * Not the script file that would be executed to creat the graph
     */
    virtual void dump(std::ostream& out, std::string& plotname) const = 0;

    /**
     * Creat a file with the current command for plotting.
     * @param filename The name of the file to be written which contains the commands to plot the graph.
     */
    void dump(const std::string& filename) const;

    /**
     * Creat a file with the current command for plotting.
     * @param filename The name of the file to be written which contains the commands to plot the graph.
     */
    static void plot(const Config &conf, Graph* gplot);

    /**
     * Function to plot a band structure
     * @param eigenparser An EigParser object to plot
     * @param parser A ConfigParser to get the parameters for the plot
     * @param gplot The graph to plot to. If nullptr, nothing plot but data written
     * @param save What to do with the calculated data : plot ? save to file ? save raw data?
     */
    static void plotBand(EigParser &eigparser, ConfigParser &config, Graph* gplot, Graph::GraphSave save);

    /**
     * Function to plot DOS
     * @param parser A ConfigParser to get the parameters for the plot
     * @param gplot The graph to plot to. If nullptr, nothing plot but data written
     * @param save What to do with the calculated data : plot ? save to file ? save raw data?
     */
    static void plotDOS(ConfigParser &config, Graph* gplot, Graph::GraphSave save);
};

#endif  // GRAPH_HPP
