//
// Copyright © 2020 Arm Ltd and Contributors. All rights reserved.
// SPDX-License-Identifier: MIT
//

#include "armnnTfLiteParser/ITfLiteParser.hpp"
#include "ParserFlatbuffersFixture.hpp"

#include <string>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(TensorflowLiteParser)

struct LoadScopeDynamicTensorFixture : public ParserFlatbuffersFixture
{
    explicit LoadScopeDynamicTensorFixture(const std::string& shape0,
                                           const std::string& shape1,
                                           const std::string& shape2)
    {
        m_JsonString = R"(
        {
            "version": 3,
            "operator_codes": [
                {
                    "builtin_code": "AVERAGE_POOL_2D",
                    "version": 1
                },
                {
                    "builtin_code": "SOFTMAX",
                    "version": 1
                }
            ],
            "subgraphs": [
                {
                    "tensors": [
                        {
                            "shape": )" + shape0 + R"(,
                            "type": "FLOAT32",
                            "buffer": 1,
                            "name": "input0",
                            "quantization": {
                                "details_type": 0,
                                "quantized_dimension": 0
                            },
                            "is_variable": false
                        },
                        {
                            "shape": )" + shape1 + R"(,
                            "type": "FLOAT32",
                            "buffer": 3,
                            "name": "output",
                            "quantization": {
                                "details_type": 0,
                                "quantized_dimension": 0
                            },
                            "is_variable": false
                        },
                        {
                            "shape": )" + shape2 + R"(,
                            "type": "FLOAT32",
                            "buffer": 2,
                            "name": "model/average_pooling2d/AvgPool",
                            "quantization": {
                                "details_type": 0,
                                "quantized_dimension": 0
                            },
                            "is_variable": false
                        }
                    ],
                    "inputs": [
                        0
                    ],
                    "outputs": [
                        1
                    ],
                    "operators": [
                        {
                            "opcode_index": 1,
                            "inputs": [
                                2
                            ],
                            "outputs": [
                                1
                            ],
                            "builtin_options_type": "SoftmaxOptions",
                            "builtin_options": {
                                "beta": 1.0
                            },
                            "custom_options_format": "FLEXBUFFERS"
                        },
                        {
                            "opcode_index": 0,
                            "inputs": [
                                0
                            ],
                            "outputs": [
                                2
                            ],
                            "builtin_options_type": "Pool2DOptions",
                            "builtin_options": {
                                "padding": "VALID",
                                "stride_w": 2,
                                "stride_h": 2,
                                "filter_width": 2,
                                "filter_height": 2,
                                "fused_activation_function": "NONE"
                            },
                            "custom_options_format": "FLEXBUFFERS"
                        }
                    ],
                    "name": "main"
                }
            ],
            "description": "MLIR Converted.",
            "buffers": [
                {
                },
                {
                },
                {
                },
                {
                }
            ]
        }
        )";
        Setup();
    }
};

struct LoadScopeDynamicTensor0Fixture : LoadScopeDynamicTensorFixture
{
    LoadScopeDynamicTensor0Fixture() : LoadScopeDynamicTensorFixture("[ 1, 2, 3, 2 ]", "[]", "[]") {}
};

struct LoadScopeDynamicTensor1Fixture : LoadScopeDynamicTensorFixture
{
    LoadScopeDynamicTensor1Fixture() : LoadScopeDynamicTensorFixture("[ 1, 2, 4, 1 ]", "[ 1, 1, 2, 1 ]", "[]") {}
};

struct LoadScopeDynamicTensor2Fixture : LoadScopeDynamicTensorFixture
{
    LoadScopeDynamicTensor2Fixture() : LoadScopeDynamicTensorFixture("[ 1, 3, 3, 2 ]", "[ ]", "[ 1, 1, 1, 2 ]") {}
};

BOOST_FIXTURE_TEST_CASE(LoadScopeDynamicTensor0, LoadScopeDynamicTensor0Fixture)
{
    RunTest<4, armnn::DataType::Float32, armnn::DataType::Float32>(
        0,
        { {"input0", { 0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f }} },
        { {"output", { 0.26894143f, 0.7310586f }} },
        true);
}

BOOST_FIXTURE_TEST_CASE(LoadScopeDynamicTensor1, LoadScopeDynamicTensor1Fixture)
{
    RunTest<4, armnn::DataType::Float32, armnn::DataType::Float32>(
        0,
        { {"input0", { 0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f }} },
        { {"output", { 1.f, 1.f }} },
        true);
}

BOOST_FIXTURE_TEST_CASE(LoadScopeDynamicTensor2, LoadScopeDynamicTensor2Fixture)
{
  RunTest<4, armnn::DataType::Float32, armnn::DataType::Float32>(
        0,
        { {"input0", { 0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f }} },
        { {"output", { 0.7772999f, 0.22270015f }} },
        true);
}

BOOST_AUTO_TEST_SUITE_END()
