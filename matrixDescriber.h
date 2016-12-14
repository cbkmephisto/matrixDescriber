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
//  matrixDescriber.h
//  libHailins
//
//  Created by Hailin Su on 1/7/15.
//

#ifndef __libHailins__matrixDescriber__
#define __libHailins__matrixDescriber__

#include <Eigen/Dense>
#include <vector>

using namespace std;
using namespace Eigen;

namespace libcbk
{
    class MatrixDescriber
    {
    public:
        vector<float> vecCoefs;

        // input/output matrices
        MatrixXf mBody;
        MatrixXf mVarCov;
        MatrixXf mR;
        MatrixXf mB;

        bool load(const char* fileName);
        void genRs();
    };
}

#endif /* defined(__libHailins__matrixDescriber__) */
