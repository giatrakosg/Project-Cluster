//
//  Parser.cpp
//  Project-Cluster
//
//  Created by <author> on 18/11/2019.
//
//

#include "Parser.hpp"

Parser::Parser(Database *db) : db(db) {}
void Parser::parseFile(std::string &input_file) {
    std::ifstream file(input_file);
    //std::istringstream str(file);

    // We extract the first line to determine if it is a vector or curve file
    std::string         flag;
    std::getline(file, flag);
    if (flag == "vectors") {
        std::cout << "Parsing vector file " << std::endl ;
        while (!file.eof()) {
            std::vector<std::string>    m_data;

            std::string         line;
            std::getline(file, line);

            std::stringstream   lineStream(line);
            std::string         cell;

            m_data.clear();
            while(std::getline(lineStream, cell, ' '))
            {
                m_data.push_back(cell);
            }
            // This checks for a trailing comma with no data after it.
            //if (!lineStream && cell.empty())
            //{
                // If there was a trailing comma then add an empty element.
            //    m_data.push_back("");
            //}
            // We have reached the eof
            if (m_data.size() == 0) {
                continue ;
            }
            // We have stored the data in a vector of strings so we have to add them to our database
            string id = m_data[0] ;
            Vector *v = new Vector(id);
            m_data.erase(m_data.begin());
            if (m_data[m_data.size() - 1].compare("\r") == 0) {
                m_data.pop_back() ;
                //std::cout << "is r" << std::endl ;
            }
            for (size_t i = 0; i < m_data.size(); i++) {
                v->addPoint(std::stod(m_data[i]));
            }
            //m_data.pop_back();
            db->addItem(v);

            //std::cout << std::endl ;
        }
    } else if (flag == "curves") {
        std::cout << "Parsing curves file " << std::endl ;
        while (!file.eof()) {
            std::vector<std::string>    m_data;

            std::string         line;
            std::getline(file, line);

            std::stringstream   lineStream(line);
            std::string         cell;
            std::string id ;
            m_data.clear();
            std::getline(lineStream, id, '\t') ; // Get id of line
            std::getline(lineStream, cell, '\t') ; // Get number of points
            if (id.empty() || cell.empty()) {
                break ;
            }
            int npoints = stod(cell);
            //db->addCurve(id,npoints);
            //std::cout << "Inserting line with id " << id << '\n';
            // now we retrieve every point of the curve
            std::vector<std::pair<double,double>> temp;
            std::pair<double,double> p ;
            while(std::getline(lineStream, cell, ')'))
            {
                std::string point1 ;
                std::string point2 ;

                cell.erase(cell.begin()); // Remove '('
                cell.erase(cell.begin()); // Remove '('
                std::stringstream   cellStream(cell);
                //std::cout << cell << '\n';
                std::getline(cellStream,point1,',');
                std::getline(cellStream,point2);
                p.first  = std::stod(point1);
                p.second = std::stod(point2);
                temp.push_back(p);
            }
            Curve *c = new Curve(id);
            for (size_t i = 0; i < temp.size(); i++) {
                c->addPoint(temp[i].first,temp[i].second);
            }
            db->addItem(c);
            // This checks for a trailing comma with no data after it.
            //if (!lineStream && cell.empty())
            //{
                // If there was a trailing comma then add an empty element.
            //    m_data.push_back("");
            //}
            // We have reached the eof
            if (m_data.size() == 0) {
                continue ;
            }
            // We have stored the data in a vector of strings so we have to add them to our database
            //m_data.erase(m_data.begin());
            if (m_data[m_data.size() - 1].compare("\r") == 0) {
                m_data.pop_back() ;
                //std::cout << "is r" << std::endl ;
            }
            //m_data.pop_back();
            //db->addPoint(id,m_data);

            //std::cout << std::endl ;
        }
    } else {
        std::cout << "File not supported " << flag << std::endl ;

    }
    file.close();
}
Parser::~Parser() {}
