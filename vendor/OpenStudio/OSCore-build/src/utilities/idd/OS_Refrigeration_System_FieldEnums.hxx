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

#ifndef UTILITIES_IDD_OS_REFRIGERATION_SYSTEM_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_REFRIGERATION_SYSTEM_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Refrigeration_SystemFields
 *  \brief Enumeration of OS:Refrigeration:System's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Refrigeration_SystemFields, )
#else
class OS_Refrigeration_SystemFields: public ::EnumBase<OS_Refrigeration_SystemFields> {
 public: 
  enum domain 
  {
Handle, Name, RefrigeratedCaseAndWalkInListName, RefrigerationTransferLoadListName, RefrigerationCondenserName, CompressorListName, MinimumCondensingTemperature, RefrigerationSystemWorkingFluidType, SuctionTemperatureControlType, MechanicalSubcoolerName, LiquidSuctionHeatExchangerSubcoolerName, SumUASuctionPiping, SuctionPipingZoneName, EndUseSubcategory, IntercoolerType, ShellandCoilIntercoolerEffectiveness, HighStageCompressorListName,   };
  OS_Refrigeration_SystemFields()
   : EnumBase<OS_Refrigeration_SystemFields>(Handle) {} 
  OS_Refrigeration_SystemFields(const std::string &t_name) 
   : EnumBase<OS_Refrigeration_SystemFields>(t_name) {} 
  OS_Refrigeration_SystemFields(int t_value) 
   : EnumBase<OS_Refrigeration_SystemFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Refrigeration_SystemFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Refrigeration_SystemFields>::value()); }
   private:
    friend class EnumBase<OS_Refrigeration_SystemFields>;
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
{ OS_Refrigeration_SystemFields::Handle, "Handle", "Handle"},
{ OS_Refrigeration_SystemFields::Name, "Name", "Name"},
{ OS_Refrigeration_SystemFields::RefrigeratedCaseAndWalkInListName, "RefrigeratedCaseAndWalkInListName", "Refrigerated CaseAndWalkInList Name"},
{ OS_Refrigeration_SystemFields::RefrigerationTransferLoadListName, "RefrigerationTransferLoadListName", "Refrigeration TransferLoad List Name"},
{ OS_Refrigeration_SystemFields::RefrigerationCondenserName, "RefrigerationCondenserName", "Refrigeration Condenser Name"},
{ OS_Refrigeration_SystemFields::CompressorListName, "CompressorListName", "CompressorList Name"},
{ OS_Refrigeration_SystemFields::MinimumCondensingTemperature, "MinimumCondensingTemperature", "Minimum Condensing Temperature"},
{ OS_Refrigeration_SystemFields::RefrigerationSystemWorkingFluidType, "RefrigerationSystemWorkingFluidType", "Refrigeration System Working Fluid Type"},
{ OS_Refrigeration_SystemFields::SuctionTemperatureControlType, "SuctionTemperatureControlType", "Suction Temperature Control Type"},
{ OS_Refrigeration_SystemFields::MechanicalSubcoolerName, "MechanicalSubcoolerName", "Mechanical Subcooler Name"},
{ OS_Refrigeration_SystemFields::LiquidSuctionHeatExchangerSubcoolerName, "LiquidSuctionHeatExchangerSubcoolerName", "Liquid Suction Heat Exchanger Subcooler Name"},
{ OS_Refrigeration_SystemFields::SumUASuctionPiping, "SumUASuctionPiping", "Sum UA Suction Piping"},
{ OS_Refrigeration_SystemFields::SuctionPipingZoneName, "SuctionPipingZoneName", "Suction Piping Zone Name"},
{ OS_Refrigeration_SystemFields::EndUseSubcategory, "EndUseSubcategory", "End-Use Subcategory"},
{ OS_Refrigeration_SystemFields::IntercoolerType, "IntercoolerType", "Intercooler Type"},
{ OS_Refrigeration_SystemFields::ShellandCoilIntercoolerEffectiveness, "ShellandCoilIntercoolerEffectiveness", "Shell-and-Coil Intercooler Effectiveness"},
{ OS_Refrigeration_SystemFields::HighStageCompressorListName, "HighStageCompressorListName", "High-Stage CompressorList Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Refrigeration_SystemFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Refrigeration_SystemFields> OptionalOS_Refrigeration_SystemFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_REFRIGERATION_SYSTEM_FIELDENUMS_HXX
