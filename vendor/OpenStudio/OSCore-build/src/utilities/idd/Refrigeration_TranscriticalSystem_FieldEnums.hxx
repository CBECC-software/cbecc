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

#ifndef UTILITIES_IDD_REFRIGERATION_TRANSCRITICALSYSTEM_FIELDENUMS_HXX
#define UTILITIES_IDD_REFRIGERATION_TRANSCRITICALSYSTEM_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Refrigeration_TranscriticalSystemFields
 *  \brief Enumeration of Refrigeration:TranscriticalSystem's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Refrigeration_TranscriticalSystemFields, )
#else
class Refrigeration_TranscriticalSystemFields: public ::EnumBase<Refrigeration_TranscriticalSystemFields> {
 public: 
  enum domain 
  {
Name, SystemType, MediumTemperatureRefrigeratedCaseorWalkinorCaseAndWalkInListName, LowTemperatureRefrigeratedCaseorWalkinorCaseAndWalkInListName, RefrigerationGasCoolerName, HighPressureCompressororCompressorListName, LowPressureCompressororCompressorListName, ReceiverPressure, SubcoolerEffectiveness, RefrigerationSystemWorkingFluidType, SumUASuctionPipingforMediumTemperatureLoads, MediumTemperatureSuctionPipingZoneName, SumUASuctionPipingforLowTemperatureLoads, LowTemperatureSuctionPipingZoneName, EndUseSubcategory,   };
  Refrigeration_TranscriticalSystemFields()
   : EnumBase<Refrigeration_TranscriticalSystemFields>(Name) {} 
  Refrigeration_TranscriticalSystemFields(const std::string &t_name) 
   : EnumBase<Refrigeration_TranscriticalSystemFields>(t_name) {} 
  Refrigeration_TranscriticalSystemFields(int t_value) 
   : EnumBase<Refrigeration_TranscriticalSystemFields>(t_value) {} 
  static std::string enumName() 
  { return "Refrigeration_TranscriticalSystemFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Refrigeration_TranscriticalSystemFields>::value()); }
   private:
    friend class EnumBase<Refrigeration_TranscriticalSystemFields>;
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
{ Refrigeration_TranscriticalSystemFields::Name, "Name", "Name"},
{ Refrigeration_TranscriticalSystemFields::SystemType, "SystemType", "System Type"},
{ Refrigeration_TranscriticalSystemFields::MediumTemperatureRefrigeratedCaseorWalkinorCaseAndWalkInListName, "MediumTemperatureRefrigeratedCaseorWalkinorCaseAndWalkInListName", "Medium Temperature Refrigerated Case or Walkin or CaseAndWalkInList Name"},
{ Refrigeration_TranscriticalSystemFields::LowTemperatureRefrigeratedCaseorWalkinorCaseAndWalkInListName, "LowTemperatureRefrigeratedCaseorWalkinorCaseAndWalkInListName", "Low Temperature Refrigerated Case or Walkin or CaseAndWalkInList Name"},
{ Refrigeration_TranscriticalSystemFields::RefrigerationGasCoolerName, "RefrigerationGasCoolerName", "Refrigeration Gas Cooler Name"},
{ Refrigeration_TranscriticalSystemFields::HighPressureCompressororCompressorListName, "HighPressureCompressororCompressorListName", "High Pressure Compressor or CompressorList Name"},
{ Refrigeration_TranscriticalSystemFields::LowPressureCompressororCompressorListName, "LowPressureCompressororCompressorListName", "Low Pressure Compressor or CompressorList Name"},
{ Refrigeration_TranscriticalSystemFields::ReceiverPressure, "ReceiverPressure", "Receiver Pressure"},
{ Refrigeration_TranscriticalSystemFields::SubcoolerEffectiveness, "SubcoolerEffectiveness", "Subcooler Effectiveness"},
{ Refrigeration_TranscriticalSystemFields::RefrigerationSystemWorkingFluidType, "RefrigerationSystemWorkingFluidType", "Refrigeration System Working Fluid Type"},
{ Refrigeration_TranscriticalSystemFields::SumUASuctionPipingforMediumTemperatureLoads, "SumUASuctionPipingforMediumTemperatureLoads", "Sum UA Suction Piping for Medium Temperature Loads"},
{ Refrigeration_TranscriticalSystemFields::MediumTemperatureSuctionPipingZoneName, "MediumTemperatureSuctionPipingZoneName", "Medium Temperature Suction Piping Zone Name"},
{ Refrigeration_TranscriticalSystemFields::SumUASuctionPipingforLowTemperatureLoads, "SumUASuctionPipingforLowTemperatureLoads", "Sum UA Suction Piping for Low Temperature Loads"},
{ Refrigeration_TranscriticalSystemFields::LowTemperatureSuctionPipingZoneName, "LowTemperatureSuctionPipingZoneName", "Low Temperature Suction Piping Zone Name"},
{ Refrigeration_TranscriticalSystemFields::EndUseSubcategory, "EndUseSubcategory", "End-Use Subcategory"},
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
  inline std::ostream &operator<<(std::ostream &os, const Refrigeration_TranscriticalSystemFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Refrigeration_TranscriticalSystemFields> OptionalRefrigeration_TranscriticalSystemFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_REFRIGERATION_TRANSCRITICALSYSTEM_FIELDENUMS_HXX
