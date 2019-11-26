/*
 * Sponsored License - for use in support of a program or activity
 * sponsored by MathWorks.  Not for government, commercial or other
 * non-sponsored organizational use.
 * File: _coder_ACC_P_test_info.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 15-Oct-2019 17:25:40
 */

/* Include Files */
#include "_coder_ACC_P_test_info.h"

/* Function Definitions */

/*
 * Arguments    : void
 * Return Type  : const mxArray *
 */
const mxArray *emlrtMexFcnResolvedFunctionsInfo()
{
  const mxArray *nameCaptureInfo;
  const char * data[7] = {
    "789ced57cd6ed34010de54a5a2872273e1e7049c2bb2a154d072aa139a2625490389aa281532b6b3495cf627b537917bcb6b20f1001cb9d123475e000ebc0777"
    "ec244e62a3954dd3bafc78246b3dfa9cf96627e3f9bc20552ca70000379c6bc9b9c05d30b2b5f102a4c9ba04fc16c453937539e07b766d82ac05f0f793556794",
    "239b8f1d6c5054e9130d998e435582a6615a8c1854a5bc7eda43c04416c303d41a216d03a3ba415089cd3905c371487e0e9a3a2ee4dee7ba487f5beb136076ad"
    "59ba78de0173f5f920d8ffb2ff71617db282fa4801fc68f775ee19acf74d8e91c6b8d23399df3b463a7f48548e55cd751577cb50cee594aac291c5d3c49ff71b",
    "415e2b11f30eae9ead82eb3367f87c278c2f6a9d56023e983e37460cca896a87ef2f8c2f68a2ffc5338fefe339f9bcf8fb217c1e7e542c3546ad503559c754c9"
    "7db7672d5896eb25390b5f6d641e6d699033863566434430c48606c76d0111766ee0b852f1f7c3e7b3dbabdfe458fb0fc4dcef57c8670be245edbf5b023e2980",
    "9b2799deb1616dcae449f529ad6a8dc72f0eadec2c8f6a084f581e40e0c7153f99e77ef3cff3bd9d8beab79b023e29803b234c21dcd1674be922dc1b7d01b876"
    "5573feec9c7c5efc5a089f872f32e759cf82bfd46dd230f1f5cbf0dd9d6132effff679df2cb7edc37d7bbba2772bcdda5e89765a2c93ff77e6fd17c1efa3d651",
    "15c49702f825bccf0f744608a38aee9e58bce349bcfd7830d583a1205ed43ade13f049015c672d67efce372c32a98ad38695ed1b9817a9733c44a6a12fac0b51"
    "cf1b2dd6d730ba385d6808f9fcf86ff7917bad8faa06d7bdb2c160d9d224465df8f4e3fbd744172e892f2e5d38189ce4e47661b0557fb979aaef12ba916fe242",
    "a20b892eb856fd6f75c1326827d1854417fe34be4417168bff1354a49795", "" };

  nameCaptureInfo = NULL;
  emlrtNameCaptureMxArrayR2016a(data, 6424U, &nameCaptureInfo);
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
  emlrtSetField(xEntryPoints, 0, "Name", emlrtMxCreateString("ACC_P_test"));
  emlrtSetField(xEntryPoints, 0, "NumberOfInputs", emlrtMxCreateDoubleScalar(6.0));
  emlrtSetField(xEntryPoints, 0, "NumberOfOutputs", emlrtMxCreateDoubleScalar
                (1.0));
  emlrtSetField(xEntryPoints, 0, "ConstantInputs", xInputs);
  emlrtSetField(xEntryPoints, 0, "FullPath", emlrtMxCreateString(
    "C:\\Turtlebot_pro\\Turtlebot_project-matlab_pro_file\\ACC_P_test.m"));
  emlrtSetField(xEntryPoints, 0, "TimeStamp", emlrtMxCreateDoubleScalar
                (737713.72583333333));
  xResult = emlrtCreateStructMatrix(1, 1, 4, *(const char * (*)[4])&b_fldNames[0]);
  emlrtSetField(xResult, 0, "Version", emlrtMxCreateString(
    "9.5.0.944444 (R2018b)"));
  emlrtSetField(xResult, 0, "ResolvedFunctions", (mxArray *)
                emlrtMexFcnResolvedFunctionsInfo());
  emlrtSetField(xResult, 0, "EntryPoints", xEntryPoints);
  return xResult;
}

/*
 * File trailer for _coder_ACC_P_test_info.c
 *
 * [EOF]
 */
