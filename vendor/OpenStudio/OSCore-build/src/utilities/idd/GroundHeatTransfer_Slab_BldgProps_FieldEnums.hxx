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

#ifndef UTILITIES_IDD_GROUNDHEATTRANSFER_SLAB_BLDGPROPS_FIELDENUMS_HXX
#define UTILITIES_IDD_GROUNDHEATTRANSFER_SLAB_BLDGPROPS_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class GroundHeatTransfer_Slab_BldgPropsFields
 *  \brief Enumeration of GroundHeatTransfer:Slab:BldgProps's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(GroundHeatTransfer_Slab_BldgPropsFields, )
#else
class GroundHeatTransfer_Slab_BldgPropsFields: public ::EnumBase<GroundHeatTransfer_Slab_BldgPropsFields> {
 public: 
  enum domain 
  {
IYRS_Numberofyearstoiterate, Shape_Slabshape, HBLDG_Buildingheight, TIN1_JanuaryIndoorAverageTemperatureSetpoint, TIN2_FebruaryIndoorAverageTemperatureSetpoint, TIN3_MarchIndoorAverageTemperatureSetpoint, TIN4_AprilIndoorAverageTemperatureSetpoint, TIN5_MayIndoorAverageTemperatureSetpoint, TIN6_JuneIndoorAverageTemperatureSetpoint, TIN7_JulyIndoorAverageTemperatureSetpoint, TIN8_AugustIndoorAverageTemperatureSetpoint, TIN9_SeptemberIndoorAverageTemperatureSetpoint, TIN10_OctoberIndoorAverageTemperatureSetpoint, TIN11_NovemberIndoorAverageTemperatureSetpoint, TIN12_DecemberIndoorAverageTemperatureSetpoint, TINAmp_DailyIndoorsinewavevariationamplitude, ConvTol_ConvergenceTolerance,   };
  GroundHeatTransfer_Slab_BldgPropsFields()
   : EnumBase<GroundHeatTransfer_Slab_BldgPropsFields>(IYRS_Numberofyearstoiterate) {} 
  GroundHeatTransfer_Slab_BldgPropsFields(const std::string &t_name) 
   : EnumBase<GroundHeatTransfer_Slab_BldgPropsFields>(t_name) {} 
  GroundHeatTransfer_Slab_BldgPropsFields(int t_value) 
   : EnumBase<GroundHeatTransfer_Slab_BldgPropsFields>(t_value) {} 
  static std::string enumName() 
  { return "GroundHeatTransfer_Slab_BldgPropsFields"; }
  domain value() const { return static_cast<domain>(EnumBase<GroundHeatTransfer_Slab_BldgPropsFields>::value()); }
   private:
    friend class EnumBase<GroundHeatTransfer_Slab_BldgPropsFields>;
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
{ GroundHeatTransfer_Slab_BldgPropsFields::IYRS_Numberofyearstoiterate, "IYRS_Numberofyearstoiterate", "IYRS: Number of years to iterate"},
{ GroundHeatTransfer_Slab_BldgPropsFields::Shape_Slabshape, "Shape_Slabshape", "Shape: Slab shape"},
{ GroundHeatTransfer_Slab_BldgPropsFields::HBLDG_Buildingheight, "HBLDG_Buildingheight", "HBLDG: Building height"},
{ GroundHeatTransfer_Slab_BldgPropsFields::TIN1_JanuaryIndoorAverageTemperatureSetpoint, "TIN1_JanuaryIndoorAverageTemperatureSetpoint", "TIN1: January Indoor Average Temperature Setpoint"},
{ GroundHeatTransfer_Slab_BldgPropsFields::TIN2_FebruaryIndoorAverageTemperatureSetpoint, "TIN2_FebruaryIndoorAverageTemperatureSetpoint", "TIN2: February Indoor Average Temperature Setpoint"},
{ GroundHeatTransfer_Slab_BldgPropsFields::TIN3_MarchIndoorAverageTemperatureSetpoint, "TIN3_MarchIndoorAverageTemperatureSetpoint", "TIN3: March Indoor Average Temperature Setpoint"},
{ GroundHeatTransfer_Slab_BldgPropsFields::TIN4_AprilIndoorAverageTemperatureSetpoint, "TIN4_AprilIndoorAverageTemperatureSetpoint", "TIN4: April Indoor Average Temperature Setpoint"},
{ GroundHeatTransfer_Slab_BldgPropsFields::TIN5_MayIndoorAverageTemperatureSetpoint, "TIN5_MayIndoorAverageTemperatureSetpoint", "TIN5: May Indoor Average Temperature Setpoint"},
{ GroundHeatTransfer_Slab_BldgPropsFields::TIN6_JuneIndoorAverageTemperatureSetpoint, "TIN6_JuneIndoorAverageTemperatureSetpoint", "TIN6: June Indoor Average Temperature Setpoint"},
{ GroundHeatTransfer_Slab_BldgPropsFields::TIN7_JulyIndoorAverageTemperatureSetpoint, "TIN7_JulyIndoorAverageTemperatureSetpoint", "TIN7: July Indoor Average Temperature Setpoint"},
{ GroundHeatTransfer_Slab_BldgPropsFields::TIN8_AugustIndoorAverageTemperatureSetpoint, "TIN8_AugustIndoorAverageTemperatureSetpoint", "TIN8: August Indoor Average Temperature Setpoint"},
{ GroundHeatTransfer_Slab_BldgPropsFields::TIN9_SeptemberIndoorAverageTemperatureSetpoint, "TIN9_SeptemberIndoorAverageTemperatureSetpoint", "TIN9: September Indoor Average Temperature Setpoint"},
{ GroundHeatTransfer_Slab_BldgPropsFields::TIN10_OctoberIndoorAverageTemperatureSetpoint, "TIN10_OctoberIndoorAverageTemperatureSetpoint", "TIN10: October Indoor Average Temperature Setpoint"},
{ GroundHeatTransfer_Slab_BldgPropsFields::TIN11_NovemberIndoorAverageTemperatureSetpoint, "TIN11_NovemberIndoorAverageTemperatureSetpoint", "TIN11: November Indoor Average Temperature Setpoint"},
{ GroundHeatTransfer_Slab_BldgPropsFields::TIN12_DecemberIndoorAverageTemperatureSetpoint, "TIN12_DecemberIndoorAverageTemperatureSetpoint", "TIN12: December Indoor Average Temperature Setpoint"},
{ GroundHeatTransfer_Slab_BldgPropsFields::TINAmp_DailyIndoorsinewavevariationamplitude, "TINAmp_DailyIndoorsinewavevariationamplitude", "TINAmp: Daily Indoor sine wave variation amplitude"},
{ GroundHeatTransfer_Slab_BldgPropsFields::ConvTol_ConvergenceTolerance, "ConvTol_ConvergenceTolerance", "ConvTol: Convergence Tolerance"},
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
  inline std::ostream &operator<<(std::ostream &os, const GroundHeatTransfer_Slab_BldgPropsFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<GroundHeatTransfer_Slab_BldgPropsFields> OptionalGroundHeatTransfer_Slab_BldgPropsFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_GROUNDHEATTRANSFER_SLAB_BLDGPROPS_FIELDENUMS_HXX
