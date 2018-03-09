//
// Copyright © 2017 Arm Ltd. All rights reserved.
// See LICENSE file in the project root for full license information.
//

#pragma once

#include <backends/NeonWorkloadUtils.hpp>

namespace armnn
{

class NeonFullyConnectedFloat32Workload : public Float32Workload<FullyConnectedQueueDescriptor>
{
public:
    NeonFullyConnectedFloat32Workload(const FullyConnectedQueueDescriptor& descriptor, const WorkloadInfo& info);
    virtual void Execute() const override;

private:
    mutable arm_compute::NEFullyConnectedLayer m_FullyConnectedLayer;
    arm_compute::Tensor                        m_WeightsTensor;
    arm_compute::Tensor                        m_BiasesTensor;
};

} //namespace armnn





