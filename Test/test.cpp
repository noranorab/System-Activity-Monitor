#include <gtest/gtest.h>

#include "../include/linux_parser.h"

// Test fixture for disk rate tests
class test : public ::testing::Test {
protected:
    int pid_;

    void SetUp() override {
        // Set up any necessary resources for the tests
        pid_ = 12345;  // Replace with the PID you want to test
    }

    void TearDown() override {
        // Clean up any resources used by the tests
    }
};

// Test for GetDiskReadRateForPID()
TEST_F(test, GetDiskReadRateForPID) {
    double readRate = LinuxParser::GetDiskReadRateForPID(pid_);
    // Add your assertions here to validate the read rate
    EXPECT_GE(readRate, 0.0);
}

// Test for GetDiskWriteRateForPID()
TEST_F(test, GetDiskWriteRateForPID) {
    double writeRate = LinuxParser::GetDiskWriteRateForPID(pid_);
    // Add your assertions here to validate the write rate
    EXPECT_GE(writeRate, 0.0);
}

// Entry point for running the tests
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


