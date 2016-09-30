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

#ifndef UTILITIES_IDD_COIL_HEATING_ELECTRIC_MULTISTAGE_FIELDENUMS_HXX
#define UTILITIES_IDD_COIL_HEATING_ELECTRIC_MULTISTAGE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Coil_Heating_Electric_MultiStageFields
 *  \brief Enumeration of Coil:Heating:Electric:MultiStage's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Coil_Heating_Electric_MultiStageFields, )
#else
class Coil_Heating_Electric_MultiStageFields: public ::EnumBase<Coil_Heating_Electric_MultiStageFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, AirInletNodeName, AirOutletNodeName, TemperatureSetpointNodeName, NumberofStages, Stage1Efficiency, Stage1NominalCapacity, Stage2Efficiency, Stage2NominalCapacity, Stage3Efficiency, Stage3NominalCapacity, Stage4Efficiency, Stage4NominalCapacity,   };
  Coil_Heating_Electric_MultiStageFields()
   : EnumBase<Coil_Heating_Electric_MultiStageFields>(Name) {} 
  Coil_Heating_Electric_MultiStageFields(const std::string &t_name) 
   : EnumBase<Coil_Heating_Electric_MultiStageFields>(t_name) {} 
  Coil_Heating_Electric_MultiStageFields(int t_value) 
   : EnumBase<Coil_Heating_Electric_MultiStageFields>(t_value) {} 
  static std::string enumName() 
  { return "Coil_Heating_Electric_MultiStageFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Coil_Heating_Electric_MultiStageFields>::value()); }
   private:
    friend class EnumBase<Coil_Heating_Electric_MultiStageFields>;
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
{ Coil_Heating_Electric_MultiStageFields::Name, "Name", "Name"},
{ Coil_Heating_Electric_MultiStageFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ Coil_Heating_Electric_MultiStageFields::AirInletNodeName, "AirInletNodeName", "Air Inlet Node Name"},
{ Coil_Heating_Electric_MultiStageFields::AirOutletNodeName, "AirOutletNodeName", "Air Outlet Node Name"},
{ Coil_Heating_Electric_MultiStageFields::TemperatureSetpointNodeName, "TemperatureSetpointNodeName", "Temperature Setpoint Node Name"},
{ Coil_Heating_Electric_MultiStageFields::NumberofStages, "NumberofStages", "Number of Stages"},
{ Coil_Heating_Electric_MultiStageFields::Stage1Efficiency, "Stage1Efficiency", "Stage 1 Efficiency"},
{ Coil_Heating_Electric_MultiStageFields::Stage1NominalCapacity, "Stage1NominalCapacity", "Stage 1 Nominal Capacity"},
{ Coil_Heating_Electric_MultiStageFields::Stage2Efficiency, "Stage2Efficiency", "Stage 2 Efficiency"},
{ Coil_Heating_Electric_MultiStageFields::Stage2NominalCapacity, "Stage2NominalCapacity", "Stage 2 Nominal Capacity"},
{ Coil_Heating_Electric_MultiStageFields::Stage3Efficiency, "Stage3Efficiency", "Stage 3 Efficiency"},
{ Coil_Heating_Electric_MultiStageFields::Stage3NominalCapacity, "Stage3NominalCapacity", "Stage 3 Nominal Capacity"},
{ Coil_Heating_Electric_MultiStageFields::Stage4Efficiency, "Stage4Efficiency", "Stage 4 Efficiency"},
{ Coil_Heating_Electric_MultiStageFields::Stage4NominalCapacity, "Stage4NominalCapacity", "Stage 4 Nominal Capacity"},
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
  inline std::ostream &operator<<(std::ostream &os, const Coil_Heating_Electric_MultiStageFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Coil_Heating_Electric_MultiStageFields> OptionalCoil_Heating_Electric_MultiStageFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_COIL_HEATING_ELECTRIC_MULTISTAGE_FIELDENUMS_HXX
