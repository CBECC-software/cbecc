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

#ifndef UTILITIES_IDD_HUMIDIFIER_STEAM_ELECTRIC_FIELDENUMS_HXX
#define UTILITIES_IDD_HUMIDIFIER_STEAM_ELECTRIC_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Humidifier_Steam_ElectricFields
 *  \brief Enumeration of Humidifier:Steam:Electric's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Humidifier_Steam_ElectricFields, )
#else
class Humidifier_Steam_ElectricFields: public ::EnumBase<Humidifier_Steam_ElectricFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, RatedCapacity, RatedPower, RatedFanPower, StandbyPower, AirInletNodeName, AirOutletNodeName, WaterStorageTankName,   };
  Humidifier_Steam_ElectricFields()
   : EnumBase<Humidifier_Steam_ElectricFields>(Name) {} 
  Humidifier_Steam_ElectricFields(const std::string &t_name) 
   : EnumBase<Humidifier_Steam_ElectricFields>(t_name) {} 
  Humidifier_Steam_ElectricFields(int t_value) 
   : EnumBase<Humidifier_Steam_ElectricFields>(t_value) {} 
  static std::string enumName() 
  { return "Humidifier_Steam_ElectricFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Humidifier_Steam_ElectricFields>::value()); }
   private:
    friend class EnumBase<Humidifier_Steam_ElectricFields>;
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
{ Humidifier_Steam_ElectricFields::Name, "Name", "Name"},
{ Humidifier_Steam_ElectricFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ Humidifier_Steam_ElectricFields::RatedCapacity, "RatedCapacity", "Rated Capacity"},
{ Humidifier_Steam_ElectricFields::RatedPower, "RatedPower", "Rated Power"},
{ Humidifier_Steam_ElectricFields::RatedFanPower, "RatedFanPower", "Rated Fan Power"},
{ Humidifier_Steam_ElectricFields::StandbyPower, "StandbyPower", "Standby Power"},
{ Humidifier_Steam_ElectricFields::AirInletNodeName, "AirInletNodeName", "Air Inlet Node Name"},
{ Humidifier_Steam_ElectricFields::AirOutletNodeName, "AirOutletNodeName", "Air Outlet Node Name"},
{ Humidifier_Steam_ElectricFields::WaterStorageTankName, "WaterStorageTankName", "Water Storage Tank Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const Humidifier_Steam_ElectricFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Humidifier_Steam_ElectricFields> OptionalHumidifier_Steam_ElectricFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_HUMIDIFIER_STEAM_ELECTRIC_FIELDENUMS_HXX
