// https://github.com/mrdoob/three.js/blob/r129/src/core/BufferAttribute.js

#ifndef THREEPP_BUFFER_ATTRIBUTE_HPP
#define THREEPP_BUFFER_ATTRIBUTE_HPP

#include "threepp/math/Vector2.hpp"
#include "threepp/math/Vector3.hpp"
#include "threepp/math/Vector4.hpp"

#include "threepp/constants.hpp"
#include "threepp/core/UpdateRange.hpp"

#include <vector>

namespace threepp {

    template<class T>
    class BufferAttribute {

    public:
        std::string name;

        BufferAttribute(std::vector<T> array, int itemSize, bool normalized = false) : array_(std::move(array)), itemSize(itemSize), count(static_cast<int>(array.size()) / itemSize) {}

        std::vector<T> array() const {
            return this->array_;
        }

        void needsUpdate() {

            version++;
        }

        BufferAttribute<T> &setUsage(int value) {

            this->usage = value;

            return *this;
        }

        BufferAttribute<T> &copyAt(unsigned int index1, const BufferAttribute<T> &attribute, unsigned int index2) {

            index1 *= this->itemSize;
            index2 *= attribute.itemSize;

            for (auto i = 0, l = this->itemSize; i < l; i++) {

                this->array_[index1 + i] = attribute.array_[index2 + i];
            }

            return &this;
        }

        BufferAttribute<T> &copyArray(const std::vector<T> &array) {

            this->array_ = array;

            return *this;
        }

        BufferAttribute<T> &copyColorsArray(const std::vector<T> &colors) {

            int offset = 0;

            for (auto i = 0, l = colors.length; i < l; i++) {

                auto color = colors[i];

                array_[offset++] = color.r;
                array_[offset++] = color.g;
                array_[offset++] = color.b;
            }

            return *this;
        }

        BufferAttribute<T> &copyVector2sArray(const std::vector<Vector2> &vectors) {

            int offset = 0;

            for (size_t i = 0, l = vectors.size(); i < l; i++) {

                const auto vector = vectors[i];

                array_[offset++] = vector.x;
                array_[offset++] = vector.y;
            }

            return *this;
        }

        BufferAttribute<T> &copyVector3sArray(const std::vector<Vector3> &vectors) {

            int offset = 0;

            for (size_t i = 0, l = vectors.size(); i < l; i++) {

                const auto vector = vectors[i];

                array_[offset++] = vector.x;
                array_[offset++] = vector.y;
                array_[offset++] = vector.z;
            }

            return *this;
        }

        BufferAttribute<T> &copyVector4sArray(std::vector<Vector4> &vectors) {

            int offset = 0;

            for (size_t i = 0, l = vectors.size(); i < l; i++) {

                const auto vector = vectors[i];

                array_[offset++] = vector.x;
                array_[offset++] = vector.y;
                array_[offset++] = vector.z;
                array_[offset++] = vector.w;
            }

            return *this;
        }

        BufferAttribute<T> &applyMatrix3(const Matrix3 &m) {

            if (this->itemSize == 2) {

                for (size_t i = 0, l = this->count; i < l; i++) {

                    _vector2.fromBufferAttribute(this, i);
                    _vector2.applyMatrix3(m);

                    this->setXY(i, _vector2.x, _vector2.y);
                }

            } else if (this->itemSize == 3) {

                for (size_t i = 0, l = this->count; i < l; i++) {

                    _vector.fromBufferAttribute(this, i);
                    _vector.applyMatrix3(m);

                    this->setXYZ(i, _vector.x, _vector.y, _vector.z);
                }
            }

            return *this;
        }

        BufferAttribute<T> &applyMatrix4( const Matrix4 &m ) {

                for ( int i = 0, l = this->count; i < l; i ++ ) {

                    _vector.x = this->getX( i );
                    _vector.y = this->getY( i );
                    _vector.z = this->getZ( i );

                    _vector.applyMatrix4( m );

                    this->setXYZ( i, _vector.x, _vector.y, _vector.z );

                }

                return *this;

        }

        BufferAttribute<T> &applyNormalMatrix( const Matrix3 &m ) {

                for ( int i = 0, l = this->count; i < l; i ++ ) {

                    _vector.x = this->getX( i );
                    _vector.y = this->getY( i );
                    _vector.z = this->getZ( i );

                    _vector.applyNormalMatrix( m );

                    this->setXYZ( i, _vector.x, _vector.y, _vector.z );

                }

                return *this;

        }

        BufferAttribute<T> &transformDirection( const Matrix4 &m ) {

                for ( size_t i = 0, l = this->count; i < l; i ++ ) {

                    _vector.x = this->getX( i );
                    _vector.y = this->getY( i );
                    _vector.z = this->getZ( i );

                    _vector.transformDirection( m );

                    this->setXYZ( i, _vector.x, _vector.y, _vector.z );

                }

                return *this;

        }

        T getX(int index) const {

            return this->array_[index * this->itemSize];
        }

        BufferAttribute<T> &setX(int index, T x) {

            this->array_[index * this->itemSize] = x;

            return *this;
        }

        T getY(int index) const {

            return this->array_[index * this->itemSize + 1];
        }

        BufferAttribute<T> setY(int index, T y) {

            this->array_[index * this->itemSize + 1] = y;

            return *this;
        }

        T getZ(int index) const {

            return this->array_[index * this->itemSize + 2];
        }

        BufferAttribute<T> setZ(int index, T z) {

            this->array_[index * this->itemSize + 2] = z;

            return *this;
        }

        T getW(int index) {

            return this->array_[index * this->itemSize + 3];
        }

        BufferAttribute<T> &setW(int index, T w) {

            this->array_[index * this->itemSize + 3] = w;

            return *this;
        }

        BufferAttribute<T> &setXY( int index, T x, T y ) {

            index *= this->itemSize;

            this->array_[ index + 0 ] = x;
            this->array_[ index + 1 ] = y;

            return *this;

        }

        BufferAttribute<T> &setXYZ( int index, T x, T y, T z ) {

            index *= this->itemSize;

            this->array_[ index + 0 ] = x;
            this->array_[ index + 1 ] = y;
            this->array_[ index + 2 ] = z;

            return *this;

        }

        BufferAttribute<T> &setXYZW( int index, T x, T y, T z, T w ) {

            index *= this->itemSize;

            this->array_[ index + 0 ] = x;
            this->array_[ index + 1 ] = y;
            this->array_[ index + 2 ] = z;
            this->array_[ index + 3 ] = w;

            return *this;

        }


    private:
        std::vector<T> array_;
        int itemSize;
        int count;

        int usage = StaticDrawUsage;
        UpdateRange updateRange = {0, -1};

        unsigned int version = 0;

        inline static Vector3 _vector = Vector3();
        inline static Vector2 _vector2 = Vector2();
    };
    
}// namespace threepp

#endif//THREEPP_BUFFER_ATTRIBUTE_HPP