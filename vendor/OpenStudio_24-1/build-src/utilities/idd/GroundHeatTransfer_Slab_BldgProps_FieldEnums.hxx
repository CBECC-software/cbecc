/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) 2008-2023, Alliance for Sustainable Energy, LLC, and other contributors. All rights reserved.
*
*  Redistribution and use in source and binary forms, with or without modification, are permitted provided that the
*  following conditions are met:
*
*  (1) Redistributions of source code must retain the above copyright notice, this list of conditions and the following
*  disclaimer.
*
*  (2) Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following
*  disclaimer in the documentation and/or other materials provided with the distribution.
*
*  (3) Neither the name of the copyright holder nor the names of any contributors may be used to endorse or promote products
*  derived from this software without specific prior written permission from the respective party.
*
*  (4) Other than as required in clauses (1) and (2), distributions in any form of modifications or other derivative works
*  may not use the "OpenStudio" trademark, "OS", "os", or any other confusingly similar designation without specific prior
*  written permission from Alliance for Sustainable Energy, LLC.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER(S) AND ANY CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
*  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
*  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER(S), ANY CONTRIBUTORS, THE UNITED STATES GOVERNMENT, OR THE UNITED
*  STATES DEPARTMENT OF ENERGY, NOR ANY OF THEIR EMPLOYEES, BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
*  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
*  USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
*  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
*  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
***********************************************************************************************************************/

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
