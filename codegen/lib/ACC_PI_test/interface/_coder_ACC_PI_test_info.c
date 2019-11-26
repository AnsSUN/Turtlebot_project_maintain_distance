/*
 * Sponsored License - for use in support of a program or activity
 * sponsored by MathWorks.  Not for government, commercial or other
 * non-sponsored organizational use.
 * File: _coder_ACC_PI_test_info.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 15-Oct-2019 17:29:12
 */

/* Include Files */
#include "_coder_ACC_PI_test_info.h"

/* Function Definitions */

/*
 * Arguments    : void
 * Return Type  : const mxArray *
 */
const mxArray *emlrtMexFcnResolvedFunctionsInfo()
{
  const mxArray *nameCaptureInfo;
  const char * data[7] = {
    "789ced574b6fd34010de54a52287a270e17102ce15d9502a289c92462d49c8c390a88a5a21633b9bc4651fa9bd89d25bfe06123f8023377ae4c81f8003ff833b"
    "761ce7b16865d38743c12345e3d1e7cc379e4ce6f38244b1920000dc009e65ee7a7e7d12a7267e052c9a8827267e55887dbb3641d605fcc3c41b8c7234e45e80",
    "4d8aaa7da223cb09a846d0344d8b11936a94374e7a0858c86678805a63a46d62d430092ab3b9a0603a01d99b83a6810bb9d7f92e32ded5fb04585d7b562e9e0f"
    "c05c7f3e4a9e7f75f176697ff292fea404fc70f74dfe396cf42d8e91ceb8dab3d86274840cfe90681c6bba1baaee23c35c3eaf2a4595239ba7c942dd6f2575ad",
    "85ac5bf4be25c1f559302a6583f8c2f6694d88c1f43e0f312927da30f8f982f84493fd2ebef97c9fcec8e7e72f05f0f9f861b1dc1c8f8262b18ea591fbeeccda"
    "b0926b94733bf0f566e6d1b60e3963586743880886d8d4a137161061e7027a9d9a8c4384f3f0e5f476f27b2ed2f90311cffb12f986927c61e7ef96842f25e0d6",
    "71a67764da5b39f244794a15bdf9f8e5bebd33ab4309e009aa0348e2a8f25fd57dde93d41576de5684d8b7a470ffd84695ac7751cd5ed4fcdd94f0a704dc5969"
    "2ae18e5edb6a17e1def88dc0b565edfdd333f2f9f9eb017c3e7e9ebdcf7a36fcad6f91bf0f8cdedf19c5fbffaaefff834a7bb85f1a3eab1addea41fd4599765a",
    "2cb3f7efecffaf92ef87eda326c99f12f04bf83f3f3018218caa867b82f18f2b4bd10750cb7a5e99eac348923f6c5fef49f853026eb096d30be71d175954c369"
    "d3dee99b9817a9737c4496699c5b27c29e476c937630ba389d684af916f13f9e2bf7b331ee1adcf0db06c5b6a549843af1f9e78f6fb14e5c125f543a511b1ce7",
    "73edc260bbf16aebc4d8257473ef0017629d887562de94ace76bffad4eb4585f8f7522d689bf8d2fd689f3e5ff0565d499fd",
    "" };

  nameCaptureInfo = NULL;
  emlrtNameCaptureMxArrayR2016a(data, 6472U, &nameCaptureInfo);
  return nameCaptureInfo;
}

/*
 * Arguments    : void
 * Return Type  : mxArray *
 */
mxArray *emlrtMexFcnProperties()
{
  mxArray *xResult;
  mxArray *xEntryPoints;
  const char * fldNames[6] = { "Name", "NumberOfInputs", "NumberOfOutputs",
    "ConstantInputs", "FullPath", "TimeStamp" };

  mxArray *xInputs;
  const char * b_fldNames[4] = { "Version", "ResolvedFunctions", "EntryPoints",
    "CoverageInfo" };

  xEntryPoints = emlrtCreateStructMatrix(1, 1, 6, *(const char * (*)[6])&
    fldNames[0]);
  xInputs = emlrtCreateLogicalMatrix(1, 6);
  emlrtSetField(xEntryPoints, 0, "Name", emlrtMxCreateString("ACC_PI_test"));
  emlrtSetField(xEntryPoints, 0, "NumberOfInputs", emlrtMxCreateDoubleScalar(6.0));
  emlrtSetField(xEntryPoints, 0, "NumberOfOutputs", emlrtMxCreateDoubleScalar
                (1.0));
  emlrtSetField(xEntryPoints, 0, "ConstantInputs", xInputs);
  emlrtSetField(xEntryPoints, 0, "FullPath", emlrtMxCreateString(
    "C:\\Turtlebot_pro\\Turtlebot_project-matlab_pro_file\\ACC_PI_test.m"));
  emlrtSetField(xEntryPoints, 0, "TimeStamp", emlrtMxCreateDoubleScalar
                (737713.72825231485));
  xResult = emlrtCreateStructMatrix(1, 1, 4, *(const char * (*)[4])&b_fldNames[0]);
  emlrtSetField(xResult, 0, "Version", emlrtMxCreateString(
    "9.5.0.944444 (R2018b)"));
  emlrtSetField(xResult, 0, "ResolvedFunctions", (mxArray *)
                emlrtMexFcnResolvedFunctionsInfo());
  emlrtSetField(xResult, 0, "EntryPoints", xEntryPoints);
  return xResult;
}

/*
 * File trailer for _coder_ACC_PI_test_info.c
 *
 * [EOF]
 */
