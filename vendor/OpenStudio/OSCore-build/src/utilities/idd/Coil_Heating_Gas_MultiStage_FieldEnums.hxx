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

#ifndef UTILITIES_IDD_COIL_HEATING_GAS_MULTISTAGE_FIELDENUMS_HXX
#define UTILITIES_IDD_COIL_HEATING_GAS_MULTISTAGE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Coil_Heating_Gas_MultiStageFields
 *  \brief Enumeration of Coil:Heating:Gas:MultiStage's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Coil_Heating_Gas_MultiStageFields, )
#else
class Coil_Heating_Gas_MultiStageFields: public ::EnumBase<Coil_Heating_Gas_MultiStageFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, AirInletNodeName, AirOutletNodeName, TemperatureSetpointNodeName, PartLoadFractionCorrelationCurveName, ParasiticGasLoad, NumberofStages,   };
  Coil_Heating_Gas_MultiStageFields()
   : EnumBase<Coil_Heating_Gas_MultiStageFields>(Name) {} 
  Coil_Heating_Gas_MultiStageFields(const std::string &t_name) 
   : EnumBase<Coil_Heating_Gas_MultiStageFields>(t_name) {} 
  Coil_Heating_Gas_MultiStageFields(int t_value) 
   : EnumBase<Coil_Heating_Gas_MultiStageFields>(t_value) {} 
  static std::string enumName() 
  { return "Coil_Heating_Gas_MultiStageFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Coil_Heating_Gas_MultiStageFields>::value()); }
   private:
    friend class EnumBase<Coil_Heating_Gas_MultiStageFields>;
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
{ Coil_Heating_Gas_MultiStageFields::Name, "Name", "Name"},
{ Coil_Heating_Gas_MultiStageFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ Coil_Heating_Gas_MultiStageFields::AirInletNodeName, "AirInletNodeName", "Air Inlet Node Name"},
{ Coil_Heating_Gas_MultiStageFields::AirOutletNodeName, "AirOutletNodeName", "Air Outlet Node Name"},
{ Coil_Heating_Gas_MultiStageFields::TemperatureSetpointNodeName, "TemperatureSetpointNodeName", "Temperature Setpoint Node Name"},
{ Coil_Heating_Gas_MultiStageFields::PartLoadFractionCorrelationCurveName, "PartLoadFractionCorrelationCurveName", "Part Load Fraction Correlation Curve Name"},
{ Coil_Heating_Gas_MultiStageFields::ParasiticGasLoad, "ParasiticGasLoad", "Parasitic Gas Load"},
{ Coil_Heating_Gas_MultiStageFields::NumberofStages, "NumberofStages", "Number of Stages"},
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
  inline std::ostream &operator<<(std::ostream &os, const Coil_Heating_Gas_MultiStageFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Coil_Heating_Gas_MultiStageFields> OptionalCoil_Heating_Gas_MultiStageFields ;
#endif

/** \class Coil_Heating_Gas_MultiStageExtensibleFields
 *  \brief Enumeration of Coil:Heating:Gas:MultiStage's Idd and Idf extensible fields
 *  to be used in conjunction with ExtensibleIndex and ExtensibleGroup.
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer ExtensibleIndex.field indices. (The enumeration value names
 *  are more likely to be valid across EnergyPlus and OpenStudio releases, and will break
 *  if they become invalid.)See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Coil_Heating_Gas_MultiStageExtensibleFields, )
#else
class Coil_Heating_Gas_MultiStageExtensibleFields: public ::EnumBase<Coil_Heating_Gas_MultiStageExtensibleFields> {
 public: 
  enum domain 
  {
StageGasBurnerEfficiency, StageNominalCapacity, StageParasiticElectricLoad,   };
  Coil_Heating_Gas_MultiStageExtensibleFields()
   : EnumBase<Coil_Heating_Gas_MultiStageExtensibleFields>(StageGasBurnerEfficiency) {} 
  Coil_Heating_Gas_MultiStageExtensibleFields(const std::string &t_name) 
   : EnumBase<Coil_Heating_Gas_MultiStageExtensibleFields>(t_name) {} 
  Coil_Heating_Gas_MultiStageExtensibleFields(int t_value) 
   : EnumBase<Coil_Heating_Gas_MultiStageExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "Coil_Heating_Gas_MultiStageExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Coil_Heating_Gas_MultiStageExtensibleFields>::value()); }
   private:
    friend class EnumBase<Coil_Heating_Gas_MultiStageExtensibleFields>;
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
{ Coil_Heating_Gas_MultiStageExtensibleFields::StageGasBurnerEfficiency, "StageGasBurnerEfficiency", "Stage Gas Burner Efficiency"},
{ Coil_Heating_Gas_MultiStageExtensibleFields::StageNominalCapacity, "StageNominalCapacity", "Stage Nominal Capacity"},
{ Coil_Heating_Gas_MultiStageExtensibleFields::StageParasiticElectricLoad, "StageParasiticElectricLoad", "Stage Parasitic Electric Load"},
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
  inline std::ostream &operator<<(std::ostream &os, const Coil_Heating_Gas_MultiStageExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Coil_Heating_Gas_MultiStageExtensibleFields> OptionalCoil_Heating_Gas_MultiStageExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_COIL_HEATING_GAS_MULTISTAGE_FIELDENUMS_HXX
