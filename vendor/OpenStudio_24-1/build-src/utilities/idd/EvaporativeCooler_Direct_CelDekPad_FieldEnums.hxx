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

#ifndef UTILITIES_IDD_EVAPORATIVECOOLER_DIRECT_CELDEKPAD_FIELDENUMS_HXX
#define UTILITIES_IDD_EVAPORATIVECOOLER_DIRECT_CELDEKPAD_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class EvaporativeCooler_Direct_CelDekPadFields
 *  \brief Enumeration of EvaporativeCooler:Direct:CelDekPad's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(EvaporativeCooler_Direct_CelDekPadFields, )
#else
class EvaporativeCooler_Direct_CelDekPadFields: public ::EnumBase<EvaporativeCooler_Direct_CelDekPadFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, DirectPadArea, DirectPadDepth, RecirculatingWaterPumpPowerConsumption, AirInletNodeName, AirOutletNodeName, ControlType, WaterSupplyStorageTankName,   };
  EvaporativeCooler_Direct_CelDekPadFields()
   : EnumBase<EvaporativeCooler_Direct_CelDekPadFields>(Name) {} 
  EvaporativeCooler_Direct_CelDekPadFields(const std::string &t_name) 
   : EnumBase<EvaporativeCooler_Direct_CelDekPadFields>(t_name) {} 
  EvaporativeCooler_Direct_CelDekPadFields(int t_value) 
   : EnumBase<EvaporativeCooler_Direct_CelDekPadFields>(t_value) {} 
  static std::string enumName() 
  { return "EvaporativeCooler_Direct_CelDekPadFields"; }
  domain value() const { return static_cast<domain>(EnumBase<EvaporativeCooler_Direct_CelDekPadFields>::value()); }
   private:
    friend class EnumBase<EvaporativeCooler_Direct_CelDekPadFields>;
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
{ EvaporativeCooler_Direct_CelDekPadFields::Name, "Name", "Name"},
{ EvaporativeCooler_Direct_CelDekPadFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ EvaporativeCooler_Direct_CelDekPadFields::DirectPadArea, "DirectPadArea", "Direct Pad Area"},
{ EvaporativeCooler_Direct_CelDekPadFields::DirectPadDepth, "DirectPadDepth", "Direct Pad Depth"},
{ EvaporativeCooler_Direct_CelDekPadFields::RecirculatingWaterPumpPowerConsumption, "RecirculatingWaterPumpPowerConsumption", "Recirculating Water Pump Power Consumption"},
{ EvaporativeCooler_Direct_CelDekPadFields::AirInletNodeName, "AirInletNodeName", "Air Inlet Node Name"},
{ EvaporativeCooler_Direct_CelDekPadFields::AirOutletNodeName, "AirOutletNodeName", "Air Outlet Node Name"},
{ EvaporativeCooler_Direct_CelDekPadFields::ControlType, "ControlType", "Control Type"},
{ EvaporativeCooler_Direct_CelDekPadFields::WaterSupplyStorageTankName, "WaterSupplyStorageTankName", "Water Supply Storage Tank Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const EvaporativeCooler_Direct_CelDekPadFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<EvaporativeCooler_Direct_CelDekPadFields> OptionalEvaporativeCooler_Direct_CelDekPadFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_EVAPORATIVECOOLER_DIRECT_CELDEKPAD_FIELDENUMS_HXX
