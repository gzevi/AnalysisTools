#ifndef CTable_H
#define CTable_H

// Ian's table class taken directly from the original source
// http://cmssw.cvs.cern.ch/cgi-bin/cmssw.cgi/UserCode/IMacneill/UCSDTools/SimpleTable/

#include <iosfwd>
#include <vector>
#include <string>
#include "TString.h"
#include "AnalysisTools/LanguageTools/interface/CNumBase.h"

class CTableCellSetter;    // class for implementing CTable::setTable()
class CTableRowAppender;   // class for implementing CTable::setTable()
class CTableColumnLabeler; // class for implementing CTable::setCells()

class CTable{
    private:

    protected:
        std::vector<std::vector<std::string> > table_; // row <column>
        mutable std::vector<size_t> colWidth_;
        std::vector<std::string> colLabels_;
        std::vector<std::string> rowLabels_;
        size_t width_;
        size_t height_;
        size_t defaultWidth_;
        size_t rowLabelWidth_;
        mutable size_t colLabelHeight_;
        size_t precision_;
        std::string title_;
        std::string delineator_;
        std::string lend_;
        std::string rend_;
        std::string corner_;
        std::ostream *out_;
        std::ofstream *file_;

        //configuration bools
        bool dispTitle_;
        bool dispLines_;
        bool useVertColLabels_;

        size_t calcLine() const;
        void printLine(char symbol, size_t length, bool endline=true) const;

    public:
        CTable();
        ~CTable();
        CTableColumnLabeler setTable();
        CTableCellSetter    setCells();
        void setCell(const std::string& entry, size_t r, size_t c); // index row and column from 0
        void setCell(const char* entryc, size_t r, size_t c);
        void setCell(unsigned int entryu, size_t r, size_t c);
        void setCell(int entryi, size_t r, size_t c);
        void setCell(float entryf, size_t r, size_t c);
        void setCell(double entryd, size_t r, size_t c);
        void setCell(const TString& entryTS, size_t r, size_t c);
        void setCell(const CNumBase<float>& entryn, size_t r, size_t c);
        void setCell(const CNumBase<double>& entryn, size_t r, size_t c);
        //void setCol(std::vector<std::string> col, size_t c);
        void setColLabel(const std::string& label, size_t c);
        void setColLabel(const char* labelc, size_t c);
        void setColLabel(const TString& labelTS, size_t c);
        //void setRow(std::vector<std::string> row, size_t r);
        void setRowLabel(const std::string& label, size_t r);
        void setRowLabel(const char* labelc, size_t r);
        void setRowLabel(const TString& labelTS, size_t r);
        size_t getNumRows() {return height_;}
        size_t getNumCols() {return width_;}
        void setTitle(const char* title);
        void setTitle(const std::string& title);
        void setTitle(const TString& title);
        void setPrecision(size_t precision);
        void useLines(bool line=true);
        void useTitle(bool title=true);
        void useVertColLabels(bool vert=true);
        void printTitle() const;
        void printColLabels() const;
        void print() const;
        void saveAs(const std::string& filename, bool overwrite=true);
        void saveTex(const std::string& filename);
        void printTex() const;
        std::string getTex();

        // non-memeber friend functions
        friend std::ostream& operator << (std::ostream& os, CTable& table);
};

// non-memeber friend functions
std::ostream& operator << (std::ostream& os, CTable& table);

// for the templates functions
#include "AnalysisTools/LanguageTools/src/CTable.impl.h"

#endif // #define CTable_H
