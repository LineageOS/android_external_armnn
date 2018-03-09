﻿//
// Copyright © 2017 Arm Ltd. All rights reserved.
// See LICENSE file in the project root for full license information.
//
#pragma once

#include "backends/WorkloadDataFwd.hpp"

#include <string>
#include <vector>

#include <memory>
#include <set>

#include <boost/assert.hpp>

#include "armnn/INetwork.hpp"
#include "armnn/Types.hpp"
#include "armnn/Descriptors.hpp"
#include "armnn/Tensor.hpp"
#include "ITensorHandle.hpp"

namespace armnn
{

class ITensorHandle;
class IWorkloadFactory;
class OutputSlot;
class WorkloadDataCollector;

class OutputHandler
{
public:
    /// @brief Sets the TensorInfo used by this output handler.
    /// @param tensorInfo TensorInfo for the output.
    void SetTensorInfo(const TensorInfo& tensorInfo);

    /// @brief Create tensor handlers used by the intermediate tensors. Does not allocate memory.
    /// @param factory Factory to be used for handler creation.
    void CreateTensorHandles(const IWorkloadFactory& factory);

    /// @brief Get the matching TensorInfo for the output
    /// @return Reference to the output TensorInfo.
    const TensorInfo& GetTensorInfo() const { return m_TensorInfo; }

    /// @brief Get the allocated tensor memory.
    /// @return Pointer to the tensor memory
    ITensorHandle* GetData() const { return m_TensorHandle.get(); }

    /// Fill the outputs for a given queue descriptor
    void CollectWorkloadOutputs(WorkloadDataCollector& dataCollector) const;

    void SetData(std::unique_ptr<ITensorHandle> data) { m_TensorHandle = std::move(data); }

    /// @brief Allocate memory for all the tensors assigned to the handlers
    void AllocateTensors();

    /// @brief Returns true if SetTensorInfo() has been called at least once on this.
    bool IsTensorInfoSet() const { return m_bTensorInfoSet; }
private:
    std::unique_ptr<ITensorHandle> m_TensorHandle;
    TensorInfo m_TensorInfo;
    bool m_bTensorInfoSet = false;
};

} //namespace armnn
