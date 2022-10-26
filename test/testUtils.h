#pragma once
#include <gtest/gtest.h>
#include <iostream>

// #define TEST_DESCRIPTION(desc) RecordProperty("description", desc)
#define TEST_DESCRIPTION(desc) std::cout << "[INFO      ] " << desc << endl