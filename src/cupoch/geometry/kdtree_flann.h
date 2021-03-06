#pragma once

#include <thrust/host_vector.h>

#include <Eigen/Core>
#include <memory>

#include "cupoch/geometry/kdtree_search_param.h"
#include "cupoch/utility/device_vector.h"

namespace flann {
template <typename T>
class Matrix;
template <typename T>
struct L2;
template <typename T>
class KDTreeCuda3dIndex;
}  // namespace flann

namespace cupoch {
namespace geometry {

class Geometry;

class KDTreeFlann {
public:
    KDTreeFlann();
    KDTreeFlann(const Geometry &geometry);
    ~KDTreeFlann();
    KDTreeFlann(const KDTreeFlann &) = delete;
    KDTreeFlann &operator=(const KDTreeFlann &) = delete;

public:
    bool SetGeometry(const Geometry &geometry);

    template <typename T>
    int Search(const utility::device_vector<T> &query,
               const KDTreeSearchParam &param,
               utility::device_vector<int> &indices,
               utility::device_vector<float> &distance2) const;

    template <typename T>
    int SearchKNN(const utility::device_vector<T> &query,
                  int knn,
                  utility::device_vector<int> &indices,
                  utility::device_vector<float> &distance2) const;

    template <typename T>
    int SearchRadius(const utility::device_vector<T> &query,
                     float radius,
                     utility::device_vector<int> &indices,
                     utility::device_vector<float> &distance2) const;

    template <typename T>
    int SearchHybrid(const utility::device_vector<T> &query,
                     float radius,
                     int max_nn,
                     utility::device_vector<int> &indices,
                     utility::device_vector<float> &distance2) const;

    template <typename T>
    int Search(const T &query,
               const KDTreeSearchParam &param,
               thrust::host_vector<int> &indices,
               thrust::host_vector<float> &distance2) const;

    template <typename T>
    int SearchKNN(const T &query,
                  int knn,
                  thrust::host_vector<int> &indices,
                  thrust::host_vector<float> &distance2) const;

    template <typename T>
    int SearchRadius(const T &query,
                     float radius,
                     thrust::host_vector<int> &indices,
                     thrust::host_vector<float> &distance2) const;

    template <typename T>
    int SearchHybrid(const T &query,
                     float radius,
                     int max_nn,
                     thrust::host_vector<int> &indices,
                     thrust::host_vector<float> &distance2) const;

    template <typename T>
    bool SetRawData(const utility::device_vector<T> &data);

protected:
    utility::device_vector<float4> data_;
    std::unique_ptr<flann::Matrix<float>> flann_dataset_;
    std::unique_ptr<flann::KDTreeCuda3dIndex<flann::L2<float>>> flann_index_;
    size_t dimension_ = 0;
    size_t dataset_size_ = 0;
};

}  // namespace geometry
}  // namespace cupoch