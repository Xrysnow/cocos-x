/**
 * Mat3 defines a 3x3 matrix. Matrix data is maintained
 * internally and is accessible via the get and set methods. Convenience methods
 * are used for matrix operations as well as generating a matrix from a given
 * set of values.
 * @autohr HALX99 2016
 * @author Mark Powell
 * @author Joshua Slack

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.
 */
#pragma once
#ifndef _CCMAT3_H_
#    define _CCMAT3_H_

#    include "base/ccMacros.h"
#    include "math/Vec3.h"
#    include "math/Vec4.h"

NS_CC_MATH_BEGIN

class Mat3
{
public:
    float m[9];

    /**
     * Constructor instantiates a new Mat3 object. The initial
     * values for the matrix is that of the identity matrix.
     *
     */
    Mat3();

    /**
     * constructs a matrix with the given values.
     *
     * @param m[0]
     *            0x0 in the matrix.
     * @param m[1]
     *            0x1 in the matrix.
     * @param m[2]
     *            0x2 in the matrix.
     * @param m[3]
     *            1x0 in the matrix.
     * @param m[4]
     *            1x1 in the matrix.
     * @param m[5]
     *            1x2 in the matrix.
     * @param m[6]
     *            2x0 in the matrix.
     * @param m[7]
     *            2x1 in the matrix.
     * @param m[8]
     *            2x2 in the matrix.
     */
    Mat3(float m[9]);

    /**
     * get retrieves a value from the matrix at the given position.
     * If the position is invalid a JmeException is thrown.
     *
     * @param i
     *            the row index.(0,1,2)
     * @param j
     *            the colum index(0,1,2)
     * @return the value at (i, j).
     */
    float get(int i, int j);

    /**
     * get(float[]) returns the matrix in row-major or column-major
     * order.
     *
     * @param data
     *            The array to return the data into. This array can be 9 or 16
     *            floats in size. Only the upper 3x3 are assigned to in the case
     *            of a 16 element array.
     * @param rowMajor
     *            True for row major storage in the array (translation in
     *            elements 3, 7, 11 for a 4x4), false for column major
     *            (translation in elements 12, 13, 14 for a 4x4).
     */
    template <size_t _Length>
    void get(float (&data)[_Length], bool rowMajor)
    {
        if (_Length == 9)
        {
            if (rowMajor)
            {
                data[0] = m[0];
                data[1] = m[1];
                data[2] = m[2];
                data[3] = m[3];
                data[4] = m[4];
                data[5] = m[5];
                data[6] = m[6];
                data[7] = m[7];
                data[8] = m[8];
            }
            else
            {
                data[0] = m[0];
                data[1] = m[3];
                data[2] = m[6];
                data[3] = m[1];
                data[4] = m[4];
                data[5] = m[7];
                data[6] = m[2];
                data[7] = m[5];
                data[8] = m[8];
            }
        }
        else if (_Length == 16)
        {
            if (rowMajor)
            {
                data[0]  = m[0];
                data[1]  = m[1];
                data[2]  = m[2];
                data[4]  = m[3];
                data[5]  = m[4];
                data[6]  = m[5];
                data[8]  = m[6];
                data[9]  = m[7];
                data[10] = m[8];
            }
            else
            {
                data[0]  = m[0];
                data[1]  = m[3];
                data[2]  = m[6];
                data[4]  = m[1];
                data[5]  = m[4];
                data[6]  = m[7];
                data[8]  = m[2];
                data[9]  = m[5];
                data[10] = m[8];
            }
        }
        else
        {
            // throw new JmeException("Array size must be 9 or 16 in Mat3.get().");
        }
    }

    /**
     * getColumn returns one of three columns specified by the
     * parameter. This column is returned as a cocos2d::Vec3 object.
     *
     * @param i
     *            the column to retrieve. Must be between 0 and 2.
     * @param store
     *            the vector object to store the result in. if null, a new one
     *            is created.
     * @return the column specified by the index.
     */
    cocos2d::Vec3 getColumn(int i);

    /**
     * getRow returns one of three rows as specified by the
     * parameter. This row is returned as a cocos2d::Vec3 object.
     *
     * @param i
     *            the row to retrieve. Must be between 0 and 2.
     * @param store
     *            the vector object to store the result in. if null, a new one
     *            is created.
     * @return the row specified by the index.
     */
    cocos2d::Vec3 getRow(int i);

    std::string toString();

    /**
     *
     * setColumn sets a particular column of this matrix to that
     * represented by the provided vector.
     *
     * @param i
     *            the column to set.
     * @param column
     *            the data to set.
     */
    void setColumn(int i, const cocos2d::Vec3& column);

    /**
     *
     * setRow sets a particular row of this matrix to that
     * represented by the provided vector.
     *
     * @param i
     *            the row to set.
     * @param row
     *            the data to set.
     */
    void setRow(int i, const cocos2d::Vec3& row);

    /**
     * set places a given value into the matrix at the given
     * position. If the position is invalid a JmeException is
     * thrown.
     *
     * @param i
     *            the row index.
     * @param j
     *            the colum index.
     * @param value
     *            the value for (i, j).
     */
    void set(int i, int j, float value);

    /**
     *
     * set sets the values of the matrix to those supplied by the
     * 3x3 two dimenion array.
     *
     * @param matrix
     *            the new values of the matrix.
     * @throws JmeException
     *             if the array is not of size 9.
     */
    void set(float matrix[3][3]);

    /**
     * Recreate Matrix using the provided axis.
     *
     * @param uAxis
     *            cocos2d::Vec3
     * @param vAxis
     *            cocos2d::Vec3
     * @param wAxis
     *            cocos2d::Vec3
     */
    void set(const cocos2d::Vec3& uAxis, const cocos2d::Vec3& vAxis, const cocos2d::Vec3& wAxis);

    /**
     * set sets the values of this matrix from an array of values
     * assuming that the data is rowMajor order;
     *
     * @param matrix
     *            the matrix to set the value to.
     */
    void set(float matrix[9]) { set(matrix, true); }

    /**
     * set sets the values of this matrix from an array of values;
     *
     * @param matrix
     *            the matrix to set the value to.
     * @param rowMajor
     *            whether the incoming data is in row or column major order.
     */
    void set(float matrix[9], bool rowMajor);

    /**
     *
     * set defines the values of the matrix based on a supplied
     * Quaternion. It should be noted that all previous values will
     * be overridden.
     *
     * @param quaternion
     *            the quaternion to create a rotational matrix from.
     */
    void set(const cocos2d::Quaternion& quaternion)
    {
        // quaternion.toRotationMatrix(this);
    }

    /**
     * loadIdentity sets this matrix to the identity matrix. Where
     * all values are zero except those along the diagonal which are one.
     *
     */
    void loadIdentity();

    /**
     *
     * @return true if this matrix is identity
     */
    bool isIdentity();

    /**
     * Creates a matrix describing a rotation around the x-axis.
     *
     * @param angle The angle of rotation (in radians).
     * @param dst A matrix to store the result in.
     */
    void rotateX(float angle);

    /**
     * Creates a matrix describing a rotation around the y-axis.
     *
     * @param angle The angle of rotation (in radians).
     * @param dst A matrix to store the result in.
     */
    void rotateY(float angle);

    /**
     * Creates a matrix describing a rotation around the z-axis.
     *
     * @param angle The angle of rotation (in radians).
     * @param dst A matrix to store the result in.
     */
    void rotateZ(float angle);

    /**
     * Creates a matrix describing a rotation around the x-axis.
     *
     * @param angle The angle of rotation (in radians).
     * @param dst A matrix to store the result in.
     */
    void rotateX(float s, float c);

    /**
     * Creates a matrix describing a rotation around the y-axis.
     *
     * @param angle The angle of rotation (in radians).
     * @param dst A matrix to store the result in.
     */
    void rotateY(float s, float c);

    /**
     * Creates a matrix describing a rotation around the z-axis.
     *
     * @param angle The angle of rotation (in radians).
     * @param dst A matrix to store the result in.
     */
    void rotateZ(float s, float c);

    /**
     * fromAngleAxis sets this matrix4f to the values specified by
     * an angle and an axis of rotation. This method creates an object, so use
     * fromAngleNormalAxis if your axis is already normalized.
     * 绕轴axis（非单位向量）旋转angle（弧度）角的3D旋转矩阵
     *
     * @param angle
     *            the angle to rotate (in radians).
     * @param axis
     *            the axis of rotation.
     */
    void createRotation(const cocos2d::Vec3& axis, float angle)
    {
        createRotation(axis, std::sin(angle), std::cos(angle));
    }

    /**
     * fromAngleNormalAxis sets this matrix4f to the values
     * specified by an angle and a normalized axis of rotation.
     *
     * @param angle
     *            the angle to rotate (in radians).
     * @param axis
     *            the axis of rotation (already normalized).
     */
    void createRotation(const cocos2d::Vec3& axis, float fSin, float fCos);

    /**
     * Creates a matrix describing a rotation around the x-axis.
     *
     * @param angle The angle of rotation (in radians).
     * @param dst A matrix to store the result in.
     */
    void createRotationX(float s, float c);

    /**
     * Creates a matrix describing a rotation around the y-axis.
     *
     * @param angle The angle of rotation (in radians).
     * @param dst A matrix to store the result in.
     */
    void createRotationY(float s, float c);

    /**
     * Creates a matrix describing a rotation around the z-axis.
     *
     * @param angle The angle of rotation (in radians).
     * @param dst A matrix to store the result in.
     */
    void createRotationZ(float s, float c);

    /**
     * Creates a scale matrix.
     *
     * @param scale The amount to scale.
     * @param dst A matrix to store the result in.
     */
    void createScale(const cocos2d::Vec3& scale);

    /**
     * Creates a scale matrix.
     *
     * @param xScale The amount to scale along the x-axis.
     * @param yScale The amount to scale along the y-axis.
     * @param zScale The amount to scale along the z-axis.
     * @param dst A matrix to store the result in.
     */
    void createScale(float xScale, float yScale, float zScale);

    /**
     * Creates a translation matrix.
     *
     * @param translation The translation.
     * @param dst A matrix to store the result in.
     */
    void createTranslation(const cocos2d::Vec3& translation);

    /**
     * Creates a translation matrix.
     *
     * @param xTranslation The translation on the x-axis.
     * @param yTranslation The translation on the y-axis.
     * @param zTranslation The translation on the z-axis.
     * @param dst A matrix to store the result in.
     */
    void createTranslation(float xTranslation, float yTranslation, float zTranslation);

    /**
     * mult multiplies this matrix by a given matrix. The result
     * matrix is returned as a new object.
     *
     * @param mat
     *            the matrix to multiply this matrix by.
     * @param product
     *            the matrix to store the result in. if null, a new Mat3 is
     *            created. It is safe for mat and product to be the same object.
     * @return a Mat3 object containing the result of this operation
     */
    Mat3& mult(const Mat3& mat) { return mult(mat, *this); }

    Mat3& mult(const Mat3& mat, Mat3& product) const;

    /**
     * Multiplies this 3x3 matrix by the 1x3 Vector vec and stores the result in
     * product.
     *
     * @param vec
     *            The cocos2d::Vec3 to multiply.
     * @return The given product vector.
     */
    cocos2d::Vec3 mult(const cocos2d::Vec3& vec) const;

    Mat3& premultAlpha(float alpha) { return multLocal(alpha); }

    /**
     * multLocal multiplies this matrix internally by a given float
     * scale factor.
     *
     * @param scale
     *            the value to scale by.
     * @return this Mat3
     */
    Mat3& multLocal(float scale);

    /**
     * add adds the values of a parameter matrix to this matrix.
     *
     * @param mat
     *            the matrix to add to this.
     */
    Mat3& addLocal(const Mat3& mat);

    /**
     * mult multiplies this matrix by a given matrix. The result
     * matrix is saved in the current matrix. If the given matrix is null,
     * nothing happens. The current matrix is returned. This is equivalent to
     * this*=mat
     *
     * @param mat
     *            the matrix to multiply this matrix by.
     * @return This matrix, after the multiplication
     */
    /*void multLocal() {

        return mult(mat, this);
    }*/

    /**
     * Transposes this matrix in place. Returns this matrix for chaining
     *
     * @return This matrix after transpose
     */
    Mat3& transposeLocal();

    /**
     * Inverts this matrix and stores it in the given store.
     *
     * @return The store
     */
    Mat3 invertNew(void);

    /**
     * Inverts this matrix locally.
     *
     * @return this
     */
    Mat3& invertLocal();

    /**
     * Places the adjoint of this matrix in store (creates store if null.)
     *
     * @param store
     *            The matrix to store the result in. If null, a new matrix is
     *            created.
     * @return store
     */
    Mat3 adjoint();

    /**
     * determinant generates the determinate of this matrix.
     *
     * @return the determinate
     */
    float determinant();

    /**
     * Sets all of the values in this matrix to zero.
     *
     * @return this matrix
     */
    Mat3& zero();

    /**
     * transposeNew returns a transposed version of this matrix.
     *
     * @return The new Mat3 object.
     */
    Mat3 transposeNew();

    /**
     * are these two matrices the same? they are is they both have the same mXX
     * values.
     *
     * @param o
     *            the object to compare for equality
     * @return true if they are equal
     */
    bool equals(const Mat3& o) const;

    /**
     * A function for creating a rotation matrix that rotates a vector called
     * "start" into another vector called "end".
     *
     * @param start
     *            normalized non-zero starting vector
     * @param end
     *            normalized non-zero ending vector
     * @see "Tomas M?ller, John Hughes /"Efficiently Building a Matrix to Rotate
     *      / One Vector to Another/" Journal of Graphics Tools, 4(4):1-4, 1999"
     */
    void fromStartEndVectors(cocos2d::Vec3 start, cocos2d::Vec3 end);

    /**
     * scale scales the operation performed by this matrix on a
     * per-component basis.
     *
     * @param scale
     *            The scale applied to each of the X, Y and Z output values.
     */
    void scale(const cocos2d::Vec3& scale);

    static bool equalIdentity(const Mat3& mat);
};

NS_CC_MATH_END

#endif
