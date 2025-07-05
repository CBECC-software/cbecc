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

#ifndef UTILITIES_IDD_OS_PHOTOVOLTAICPERFORMANCE_SANDIA_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_PHOTOVOLTAICPERFORMANCE_SANDIA_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_PhotovoltaicPerformance_SandiaFields
 *  \brief Enumeration of OS:PhotovoltaicPerformance:Sandia's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_PhotovoltaicPerformance_SandiaFields, )
#else
class OS_PhotovoltaicPerformance_SandiaFields: public ::EnumBase<OS_PhotovoltaicPerformance_SandiaFields> {
 public: 
  enum domain 
  {
Handle, Name, ActiveArea, NumberofCellsinSeries, NumberofCellsinParallel, ShortCircuitCurrent, OpenCircuitVoltage, CurrentatMaximumPowerPoint, VoltageatMaximumPowerPoint, SandiaDatabaseParameteraIsc, SandiaDatabaseParameteraImp, SandiaDatabaseParameterc0, SandiaDatabaseParameterc1, SandiaDatabaseParameterBVoc0, SandiaDatabaseParametermBVoc, SandiaDatabaseParameterBVmp0, SandiaDatabaseParametermBVmp, DiodeFactor, SandiaDatabaseParameterc2, SandiaDatabaseParameterc3, SandiaDatabaseParametera0, SandiaDatabaseParametera1, SandiaDatabaseParametera2, SandiaDatabaseParametera3, SandiaDatabaseParametera4, SandiaDatabaseParameterb0, SandiaDatabaseParameterb1, SandiaDatabaseParameterb2, SandiaDatabaseParameterb3, SandiaDatabaseParameterb4, SandiaDatabaseParameterb5, SandiaDatabaseParameterDelta_Tc_, SandiaDatabaseParameterfd, SandiaDatabaseParametera, SandiaDatabaseParameterb, SandiaDatabaseParameterc4, SandiaDatabaseParameterc5, SandiaDatabaseParameterIx0, SandiaDatabaseParameterIxx0, SandiaDatabaseParameterc6, SandiaDatabaseParameterc7,   };
  OS_PhotovoltaicPerformance_SandiaFields()
   : EnumBase<OS_PhotovoltaicPerformance_SandiaFields>(Handle) {} 
  OS_PhotovoltaicPerformance_SandiaFields(const std::string &t_name) 
   : EnumBase<OS_PhotovoltaicPerformance_SandiaFields>(t_name) {} 
  OS_PhotovoltaicPerformance_SandiaFields(int t_value) 
   : EnumBase<OS_PhotovoltaicPerformance_SandiaFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_PhotovoltaicPerformance_SandiaFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_PhotovoltaicPerformance_SandiaFields>::value()); }
   private:
    friend class EnumBase<OS_PhotovoltaicPerformance_SandiaFields>;
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
{ OS_PhotovoltaicPerformance_SandiaFields::Handle, "Handle", "Handle"},
{ OS_PhotovoltaicPerformance_SandiaFields::Name, "Name", "Name"},
{ OS_PhotovoltaicPerformance_SandiaFields::ActiveArea, "ActiveArea", "Active Area"},
{ OS_PhotovoltaicPerformance_SandiaFields::NumberofCellsinSeries, "NumberofCellsinSeries", "Number of Cells in Series"},
{ OS_PhotovoltaicPerformance_SandiaFields::NumberofCellsinParallel, "NumberofCellsinParallel", "Number of Cells in Parallel"},
{ OS_PhotovoltaicPerformance_SandiaFields::ShortCircuitCurrent, "ShortCircuitCurrent", "Short Circuit Current"},
{ OS_PhotovoltaicPerformance_SandiaFields::OpenCircuitVoltage, "OpenCircuitVoltage", "Open Circuit Voltage"},
{ OS_PhotovoltaicPerformance_SandiaFields::CurrentatMaximumPowerPoint, "CurrentatMaximumPowerPoint", "Current at Maximum Power Point"},
{ OS_PhotovoltaicPerformance_SandiaFields::VoltageatMaximumPowerPoint, "VoltageatMaximumPowerPoint", "Voltage at Maximum Power Point"},
{ OS_PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParameteraIsc, "SandiaDatabaseParameteraIsc", "Sandia Database Parameter aIsc"},
{ OS_PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParameteraImp, "SandiaDatabaseParameteraImp", "Sandia Database Parameter aImp"},
{ OS_PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParameterc0, "SandiaDatabaseParameterc0", "Sandia Database Parameter c0"},
{ OS_PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParameterc1, "SandiaDatabaseParameterc1", "Sandia Database Parameter c1"},
{ OS_PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParameterBVoc0, "SandiaDatabaseParameterBVoc0", "Sandia Database Parameter BVoc0"},
{ OS_PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParametermBVoc, "SandiaDatabaseParametermBVoc", "Sandia Database Parameter mBVoc"},
{ OS_PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParameterBVmp0, "SandiaDatabaseParameterBVmp0", "Sandia Database Parameter BVmp0"},
{ OS_PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParametermBVmp, "SandiaDatabaseParametermBVmp", "Sandia Database Parameter mBVmp"},
{ OS_PhotovoltaicPerformance_SandiaFields::DiodeFactor, "DiodeFactor", "Diode Factor"},
{ OS_PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParameterc2, "SandiaDatabaseParameterc2", "Sandia Database Parameter c2"},
{ OS_PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParameterc3, "SandiaDatabaseParameterc3", "Sandia Database Parameter c3"},
{ OS_PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParametera0, "SandiaDatabaseParametera0", "Sandia Database Parameter a0"},
{ OS_PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParametera1, "SandiaDatabaseParametera1", "Sandia Database Parameter a1"},
{ OS_PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParametera2, "SandiaDatabaseParametera2", "Sandia Database Parameter a2"},
{ OS_PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParametera3, "SandiaDatabaseParametera3", "Sandia Database Parameter a3"},
{ OS_PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParametera4, "SandiaDatabaseParametera4", "Sandia Database Parameter a4"},
{ OS_PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParameterb0, "SandiaDatabaseParameterb0", "Sandia Database Parameter b0"},
{ OS_PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParameterb1, "SandiaDatabaseParameterb1", "Sandia Database Parameter b1"},
{ OS_PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParameterb2, "SandiaDatabaseParameterb2", "Sandia Database Parameter b2"},
{ OS_PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParameterb3, "SandiaDatabaseParameterb3", "Sandia Database Parameter b3"},
{ OS_PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParameterb4, "SandiaDatabaseParameterb4", "Sandia Database Parameter b4"},
{ OS_PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParameterb5, "SandiaDatabaseParameterb5", "Sandia Database Parameter b5"},
{ OS_PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParameterDelta_Tc_, "SandiaDatabaseParameterDelta_Tc_", "Sandia Database Parameter Delta(Tc)"},
{ OS_PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParameterfd, "SandiaDatabaseParameterfd", "Sandia Database Parameter fd"},
{ OS_PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParametera, "SandiaDatabaseParametera", "Sandia Database Parameter a"},
{ OS_PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParameterb, "SandiaDatabaseParameterb", "Sandia Database Parameter b"},
{ OS_PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParameterc4, "SandiaDatabaseParameterc4", "Sandia Database Parameter c4"},
{ OS_PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParameterc5, "SandiaDatabaseParameterc5", "Sandia Database Parameter c5"},
{ OS_PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParameterIx0, "SandiaDatabaseParameterIx0", "Sandia Database Parameter Ix0"},
{ OS_PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParameterIxx0, "SandiaDatabaseParameterIxx0", "Sandia Database Parameter Ixx0"},
{ OS_PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParameterc6, "SandiaDatabaseParameterc6", "Sandia Database Parameter c6"},
{ OS_PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParameterc7, "SandiaDatabaseParameterc7", "Sandia Database Parameter c7"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_PhotovoltaicPerformance_SandiaFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_PhotovoltaicPerformance_SandiaFields> OptionalOS_PhotovoltaicPerformance_SandiaFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_PHOTOVOLTAICPERFORMANCE_SANDIA_FIELDENUMS_HXX
