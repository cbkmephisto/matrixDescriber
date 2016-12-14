/*
 * Copyright (c) 2016 Hailin Su, ISU NBCEC
 *
 * This file is part of matrixDescriber.
 *
 * matrixDescriber is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * matrixDescriber is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU General Lesser Public License
 * along with matrixDescriber. If not, see <http://www.gnu.org/licenses/>.
 */

//
//  matrixDescriber.cpp
//  libHailins
//
//  Created by Hailin Su on 1/7/15.
//

#include "matrixDescriber.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;
using namespace Eigen;

namespace libcbk
{
    bool MatrixDescriber::load(const char* fileName)
    {
        bool ret(false);
        if(vecCoefs.size())
            vector<float>().swap(vecCoefs);

        ifstream infs(fileName);
        if(infs)            // input file valid
        {
            stringstream sst, ssf;
            string aLine, stmp;
            float ft;
            unsigned firstColCount(0), colCount, rowCount(0);

            while(getline(infs, aLine)) // for each read line
            {
                sst << aLine;
                colCount=0;
                while(sst>>stmp)          // convert content to float
                {
                    ssf << stmp;
                    if(ssf >> ft)           // ignore string
                    {
                        ++colCount;         // remember how many cols in the current line
                        vecCoefs.push_back(ft);
                    }
                    ssf.str("");
                    ssf.clear();
                }
                sst.clear();

                ++rowCount;
                if(firstColCount)   // all the rest lines, compare consistancy of column number
                {
                    if(colCount!=firstColCount)
                    {
                        cerr << "ERROR Inconsistency of column number detected." << endl;
                        cerr << "    line " << rowCount << endl;
                        break;
                    }
                }
                else if(colCount)           // first data line
                    firstColCount=colCount;
                // else
                // skip header line
            }
            infs.close();

            if(firstColCount==colCount) // if no error
            {
                // this 'new' does not invoke the memory allocator
                //new (&mtxBody) Map<MatrixXf>(vecCoefs.data(), rowCount, firstColCount);
                cout << "MatrixDescriber::load() finished successfully, returning matrix (" << rowCount << ", " << firstColCount << ")" << endl;
                Map<MatrixXf> mtxTmp(vecCoefs.data(), firstColCount, rowCount);
                // this is a col-majored initialization, so it is transposed
                mBody=mtxTmp.transpose();
                //            cout << mtxBody << endl;
                ret=true;
            }
        }
        return ret;
    }

    void MatrixDescriber::genRs()
    {
        const unsigned long rows(mBody.rows());
        const unsigned long cols(mBody.cols());

        VectorXf v1r(rows);
        unsigned i, j;
        for(i=0; i<rows; ++i)    // vector of 1's, size==rows
            v1r(i)=1;

//        cout << "getting sum" << endl;
        VectorXf vSum(rows);
        vSum=v1r.transpose()*mBody;
//        cout << vSum.transpose() << endl;

//        cout << "getting mean" << endl;
        MatrixXf mMean(rows, cols);
        // vSum should be a row vector but eigen just stored it as col vector
        mMean=v1r*(vSum.transpose()/rows);
//        cout << mMean << endl;

//        cout << "getting deviation" << endl;
        MatrixXf mD(rows, cols);
        mD=mBody-mMean;
//        cout << mD << endl;

        cout << endl << "======== DESCRIPTION" << endl;
        cout << right << setfill(' ') << setw(8) << "min";
        for(i=0; i<cols; ++i)
            cout << right << setfill(' ')
            << setw(12) << mBody.col(i).minCoeff();
        cout << endl;

        cout << right << setfill(' ') << setw(8) << "mean";
        for(i=0; i<cols; ++i)
            cout << right << setfill(' ')
            << setw(12) << mBody.col(i).mean();
        cout << endl;

        cout << right << setfill(' ') << setw(8) << "max";
        for(i=0; i<cols; ++i)
            cout << right << setfill(' ')
            << setw(12) << mBody.col(i).maxCoeff();
        cout << endl << endl;


        cout << "======== VARIANCE / COVARIANCE MATRIX" << endl;
        mVarCov=mD.transpose()*mD/(rows-1);
        cout << mVarCov << endl << endl;

        MatrixXf mSD(cols, cols), mSDinv(cols, cols);
//      cout << "getting mSD/mSDinv" << endl;
        for(i=0; i<cols; ++i)
            for(j=0; j<cols; ++j)
            {
                if(i!=j)    // off diag
                    mSD(i, j)=mSD(j, i)=mSDinv(i, j)=mSDinv(j, i)=0;
                else        // diag
                {
                    mSD(i, j)=sqrt(mVarCov(i, j));
                    mSDinv(i, j)=1/mSD(i, j);
                }
            }
//        cout << mSD << endl << mSDinv << endl;

        cout << "======== CORRELATION COEFFICIENT MATRIX" << endl;
        mR=mSDinv*mVarCov*mSDinv;
        cout << mR << endl << endl;

        cout << "======== REGRESSION COEFFICIENT MATRIX: mB(r, c)=b(r/c)" << endl;
        mB=MatrixXf(cols, cols);
        for(i=0; i<cols; ++i)
            for(j=0; j<cols; ++j)
                mB(i, j)=mR(i, j)*(mSD(i, i)/mSD(j, j));    // mB(r, c)=b(r/c)
        cout << mB << endl;
    }
}

int main(int argc, const char * argv[])
{
    // testCase of matrixDescriber
    if(argc!=2)
    {
        cerr << "Need an input fileName of a dense matrix." << endl;
        cerr << "  - tab/space delimited data file" << endl;
        cerr << "  - columnwise" << endl;
        cerr << "  - headers (colNames/rowNames) will be automatically ignored" << endl;
        return 0;
    }
    cout << "v20150112-1644" << endl;

    libcbk::MatrixDescriber md;
    if(md.load(argv[1]))
        md.genRs();
    else
        cerr << "something unexpected happened" << endl;
    return 0;
}
