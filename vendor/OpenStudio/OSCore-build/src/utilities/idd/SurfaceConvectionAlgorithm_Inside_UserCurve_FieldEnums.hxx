/**********************************************************************
*  Copyright (c) 2008-2016, Alliance for Sustainable Energy.
*  All rights reserved.
*
*  This library is free software; you can redistribute it and/or
*  modify it under the terms of the GNU Lesser General Public
*  License as published by the Free Software Foundation; either
*  version 2.1 of the License, or (at your option) any later version.
*
*  This library is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
*  Lesser General Public License for more details.
*
*  You should have received a copy of the GNU Lesser General Public
*  License along with this library; if not, write to the Free Software
*  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
**********************************************************************/

#ifndef UTILITIES_IDD_SURFACECONVECTIONALGORITHM_INSIDE_USERCURVE_FIELDENUMS_HXX
#define UTILITIES_IDD_SURFACECONVECTIONALGORITHM_INSIDE_USERCURVE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class SurfaceConvectionAlgorithm_Inside_UserCurveFields
 *  \brief Enumeration of SurfaceConvectionAlgorithm:Inside:UserCurve's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(SurfaceConvectionAlgorithm_Inside_UserCurveFields, )
#else
class SurfaceConvectionAlgorithm_Inside_UserCurveFields: public ::EnumBase<SurfaceConvectionAlgorithm_Inside_UserCurveFields> {
 public: 
  enum domain 
  {
Name, ReferenceTemperatureforConvectionHeatTransfer, HcFunctionofTemperatureDifferenceCurveName, HcFunctionofTemperatureDifferenceDividedbyHeightCurveName, HcFunctionofAirChangeRateCurveName, HcFunctionofAirSystemVolumeFlowRateDividedbyZonePerimeterLengthCurveName,   };
  SurfaceConvectionAlgorithm_Inside_UserCurveFields()
   : EnumBase<SurfaceConvectionAlgorithm_Inside_UserCurveFields>(Name) {} 
  SurfaceConvectionAlgorithm_Inside_UserCurveFields(const std::string &t_name) 
   : EnumBase<SurfaceConvectionAlgorithm_Inside_UserCurveFields>(t_name) {} 
  SurfaceConvectionAlgorithm_Inside_UserCurveFields(int t_value) 
   : EnumBase<SurfaceConvectionAlgorithm_Inside_UserCurveFields>(t_value) {} 
  static std::string enumName() 
  { return "SurfaceConvectionAlgorithm_Inside_UserCurveFields"; }
  domain value() const { return static_cast<domain>(EnumBase<SurfaceConvectionAlgorithm_Inside_UserCurveFields>::value()); }
   private:
    friend class EnumBase<SurfaceConvectionAlgorithm_Inside_UserCurveFields>;
    typedef std::pair<std::string, int> PT;
    typedef std::vector<PT> VecType;
    static VecType buildStringVec(bool isd)
    {
      struct evalue
      {
        int value; const char *name; const char *description;
      };
      const evalue a[] =
      {
{ SurfaceConvectionAlgorithm_Inside_UserCurveFields::Name, "Name", "Name"},
{ SurfaceConvectionAlgorithm_Inside_UserCurveFields::ReferenceTemperatureforConvectionHeatTransfer, "ReferenceTemperatureforConvectionHeatTransfer", "Reference Temperature for Convection Heat Transfer"},
{ SurfaceConvectionAlgorithm_Inside_UserCurveFields::HcFunctionofTemperatureDifferenceCurveName, "HcFunctionofTemperatureDifferenceCurveName", "Hc Function of Temperature Difference Curve Name"},
{ SurfaceConvectionAlgorithm_Inside_UserCurveFields::HcFunctionofTemperatureDifferenceDividedbyHeightCurveName, "HcFunctionofTemperatureDifferenceDividedbyHeightCurveName", "Hc Function of Temperature Difference Divided by Height Curve Name"},
{ SurfaceConvectionAlgorithm_Inside_UserCurveFields::HcFunctionofAirChangeRateCurveName, "HcFunctionofAirChangeRateCurveName", "Hc Function of Air Change Rate Curve Name"},
{ SurfaceConvectionAlgorithm_Inside_UserCurveFields::HcFunctionofAirSystemVolumeFlowRateDividedbyZonePerimeterLengthCurveName, "HcFunctionofAirSystemVolumeFlowRateDividedbyZonePerimeterLengthCurveName", "Hc Function of Air System Volume Flow Rate Divided by Zone Perimeter Length Curve Name"},
        { 0,0,0 }
      };
      VecType v;
      int i = 0;
      while (!(a[i].value == 0 && a[i].name == 0 && a[i].description == 0))
      {
        if (isd)
        {
          std::string description = a[i].description; 
          if (!description.empty())
          {
            v.push_back(PT(description, a[i].value));
          }
        } else {
          v.push_back(PT(a[i].name, a[i].value));
        }
        ++i;
      }
      return v;
    }
  
  };
  inline std::ostream &operator<<(std::ostream &os, const SurfaceConvectionAlgorithm_Inside_UserCurveFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<SurfaceConvectionAlgorithm_Inside_UserCurveFields> OptionalSurfaceConvectionAlgorithm_Inside_UserCurveFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_SURFACECONVECTIONALGORITHM_INSIDE_USERCURVE_FIELDENUMS_HXX
