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

#ifndef UTILITIES_IDD_SURFACECONVECTIONALGORITHM_OUTSIDE_ADAPTIVEMODELSELECTIONS_FIELDENUMS_HXX
#define UTILITIES_IDD_SURFACECONVECTIONALGORITHM_OUTSIDE_ADAPTIVEMODELSELECTIONS_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class SurfaceConvectionAlgorithm_Outside_AdaptiveModelSelectionsFields
 *  \brief Enumeration of SurfaceConvectionAlgorithm:Outside:AdaptiveModelSelections's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(SurfaceConvectionAlgorithm_Outside_AdaptiveModelSelectionsFields, )
#else
class SurfaceConvectionAlgorithm_Outside_AdaptiveModelSelectionsFields: public ::EnumBase<SurfaceConvectionAlgorithm_Outside_AdaptiveModelSelectionsFields> {
 public: 
  enum domain 
  {
Name, WindConvectionWindwardVerticalWallEquationSource, WindConvectionWindwardEquationVerticalWallUserCurveName, WindConvectionLeewardVerticalWallEquationSource, WindConvectionLeewardVerticalWallEquationUserCurveName, WindConvectionHorizontalRoofEquationSource, WindConvectionHorizontalRoofUserCurveName, NaturalConvectionVerticalWallEquationSource, NaturalConvectionVerticalWallEquationUserCurveName, NaturalConvectionStableHorizontalEquationSource, NaturalConvectionStableHorizontalEquationUserCurveName, NaturalConvectionUnstableHorizontalEquationSource, NaturalConvectionUnstableHorizontalEquationUserCurveName,   };
  SurfaceConvectionAlgorithm_Outside_AdaptiveModelSelectionsFields()
   : EnumBase<SurfaceConvectionAlgorithm_Outside_AdaptiveModelSelectionsFields>(Name) {} 
  SurfaceConvectionAlgorithm_Outside_AdaptiveModelSelectionsFields(const std::string &t_name) 
   : EnumBase<SurfaceConvectionAlgorithm_Outside_AdaptiveModelSelectionsFields>(t_name) {} 
  SurfaceConvectionAlgorithm_Outside_AdaptiveModelSelectionsFields(int t_value) 
   : EnumBase<SurfaceConvectionAlgorithm_Outside_AdaptiveModelSelectionsFields>(t_value) {} 
  static std::string enumName() 
  { return "SurfaceConvectionAlgorithm_Outside_AdaptiveModelSelectionsFields"; }
  domain value() const { return static_cast<domain>(EnumBase<SurfaceConvectionAlgorithm_Outside_AdaptiveModelSelectionsFields>::value()); }
   private:
    friend class EnumBase<SurfaceConvectionAlgorithm_Outside_AdaptiveModelSelectionsFields>;
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
{ SurfaceConvectionAlgorithm_Outside_AdaptiveModelSelectionsFields::Name, "Name", "Name"},
{ SurfaceConvectionAlgorithm_Outside_AdaptiveModelSelectionsFields::WindConvectionWindwardVerticalWallEquationSource, "WindConvectionWindwardVerticalWallEquationSource", "Wind Convection Windward Vertical Wall Equation Source"},
{ SurfaceConvectionAlgorithm_Outside_AdaptiveModelSelectionsFields::WindConvectionWindwardEquationVerticalWallUserCurveName, "WindConvectionWindwardEquationVerticalWallUserCurveName", "Wind Convection Windward Equation Vertical Wall User Curve Name"},
{ SurfaceConvectionAlgorithm_Outside_AdaptiveModelSelectionsFields::WindConvectionLeewardVerticalWallEquationSource, "WindConvectionLeewardVerticalWallEquationSource", "Wind Convection Leeward Vertical Wall Equation Source"},
{ SurfaceConvectionAlgorithm_Outside_AdaptiveModelSelectionsFields::WindConvectionLeewardVerticalWallEquationUserCurveName, "WindConvectionLeewardVerticalWallEquationUserCurveName", "Wind Convection Leeward Vertical Wall Equation User Curve Name"},
{ SurfaceConvectionAlgorithm_Outside_AdaptiveModelSelectionsFields::WindConvectionHorizontalRoofEquationSource, "WindConvectionHorizontalRoofEquationSource", "Wind Convection Horizontal Roof Equation Source"},
{ SurfaceConvectionAlgorithm_Outside_AdaptiveModelSelectionsFields::WindConvectionHorizontalRoofUserCurveName, "WindConvectionHorizontalRoofUserCurveName", "Wind Convection Horizontal Roof User Curve Name"},
{ SurfaceConvectionAlgorithm_Outside_AdaptiveModelSelectionsFields::NaturalConvectionVerticalWallEquationSource, "NaturalConvectionVerticalWallEquationSource", "Natural Convection Vertical Wall Equation Source"},
{ SurfaceConvectionAlgorithm_Outside_AdaptiveModelSelectionsFields::NaturalConvectionVerticalWallEquationUserCurveName, "NaturalConvectionVerticalWallEquationUserCurveName", "Natural Convection Vertical Wall Equation User Curve Name"},
{ SurfaceConvectionAlgorithm_Outside_AdaptiveModelSelectionsFields::NaturalConvectionStableHorizontalEquationSource, "NaturalConvectionStableHorizontalEquationSource", "Natural Convection Stable Horizontal Equation Source"},
{ SurfaceConvectionAlgorithm_Outside_AdaptiveModelSelectionsFields::NaturalConvectionStableHorizontalEquationUserCurveName, "NaturalConvectionStableHorizontalEquationUserCurveName", "Natural Convection Stable Horizontal Equation User Curve Name"},
{ SurfaceConvectionAlgorithm_Outside_AdaptiveModelSelectionsFields::NaturalConvectionUnstableHorizontalEquationSource, "NaturalConvectionUnstableHorizontalEquationSource", "Natural Convection Unstable Horizontal Equation Source"},
{ SurfaceConvectionAlgorithm_Outside_AdaptiveModelSelectionsFields::NaturalConvectionUnstableHorizontalEquationUserCurveName, "NaturalConvectionUnstableHorizontalEquationUserCurveName", "Natural Convection Unstable Horizontal Equation User Curve Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const SurfaceConvectionAlgorithm_Outside_AdaptiveModelSelectionsFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<SurfaceConvectionAlgorithm_Outside_AdaptiveModelSelectionsFields> OptionalSurfaceConvectionAlgorithm_Outside_AdaptiveModelSelectionsFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_SURFACECONVECTIONALGORITHM_OUTSIDE_ADAPTIVEMODELSELECTIONS_FIELDENUMS_HXX
