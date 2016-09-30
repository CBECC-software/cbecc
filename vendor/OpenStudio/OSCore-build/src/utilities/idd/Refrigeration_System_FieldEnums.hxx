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

#ifndef UTILITIES_IDD_REFRIGERATION_SYSTEM_FIELDENUMS_HXX
#define UTILITIES_IDD_REFRIGERATION_SYSTEM_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Refrigeration_SystemFields
 *  \brief Enumeration of Refrigeration:System's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Refrigeration_SystemFields, )
#else
class Refrigeration_SystemFields: public ::EnumBase<Refrigeration_SystemFields> {
 public: 
  enum domain 
  {
Name, RefrigeratedCaseorWalkinorCaseAndWalkInListName, RefrigerationTransferLoadorTransferLoadListName, RefrigerationCondenserName, CompressororCompressorListName, MinimumCondensingTemperature, RefrigerationSystemWorkingFluidType, SuctionTemperatureControlType, MechanicalSubcoolerName, LiquidSuctionHeatExchangerSubcoolerName, SumUASuctionPiping, SuctionPipingZoneName, EndUseSubcategory, NumberofCompressorStages, IntercoolerType, ShellandCoilIntercoolerEffectiveness, HighStageCompressororCompressorListName,   };
  Refrigeration_SystemFields()
   : EnumBase<Refrigeration_SystemFields>(Name) {} 
  Refrigeration_SystemFields(const std::string &t_name) 
   : EnumBase<Refrigeration_SystemFields>(t_name) {} 
  Refrigeration_SystemFields(int t_value) 
   : EnumBase<Refrigeration_SystemFields>(t_value) {} 
  static std::string enumName() 
  { return "Refrigeration_SystemFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Refrigeration_SystemFields>::value()); }
   private:
    friend class EnumBase<Refrigeration_SystemFields>;
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
{ Refrigeration_SystemFields::Name, "Name", "Name"},
{ Refrigeration_SystemFields::RefrigeratedCaseorWalkinorCaseAndWalkInListName, "RefrigeratedCaseorWalkinorCaseAndWalkInListName", "Refrigerated Case or Walkin or CaseAndWalkInList Name"},
{ Refrigeration_SystemFields::RefrigerationTransferLoadorTransferLoadListName, "RefrigerationTransferLoadorTransferLoadListName", "Refrigeration Transfer Load or TransferLoad List Name"},
{ Refrigeration_SystemFields::RefrigerationCondenserName, "RefrigerationCondenserName", "Refrigeration Condenser Name"},
{ Refrigeration_SystemFields::CompressororCompressorListName, "CompressororCompressorListName", "Compressor or CompressorList Name"},
{ Refrigeration_SystemFields::MinimumCondensingTemperature, "MinimumCondensingTemperature", "Minimum Condensing Temperature"},
{ Refrigeration_SystemFields::RefrigerationSystemWorkingFluidType, "RefrigerationSystemWorkingFluidType", "Refrigeration System Working Fluid Type"},
{ Refrigeration_SystemFields::SuctionTemperatureControlType, "SuctionTemperatureControlType", "Suction Temperature Control Type"},
{ Refrigeration_SystemFields::MechanicalSubcoolerName, "MechanicalSubcoolerName", "Mechanical Subcooler Name"},
{ Refrigeration_SystemFields::LiquidSuctionHeatExchangerSubcoolerName, "LiquidSuctionHeatExchangerSubcoolerName", "Liquid Suction Heat Exchanger Subcooler Name"},
{ Refrigeration_SystemFields::SumUASuctionPiping, "SumUASuctionPiping", "Sum UA Suction Piping"},
{ Refrigeration_SystemFields::SuctionPipingZoneName, "SuctionPipingZoneName", "Suction Piping Zone Name"},
{ Refrigeration_SystemFields::EndUseSubcategory, "EndUseSubcategory", "End-Use Subcategory"},
{ Refrigeration_SystemFields::NumberofCompressorStages, "NumberofCompressorStages", "Number of Compressor Stages"},
{ Refrigeration_SystemFields::IntercoolerType, "IntercoolerType", "Intercooler Type"},
{ Refrigeration_SystemFields::ShellandCoilIntercoolerEffectiveness, "ShellandCoilIntercoolerEffectiveness", "Shell-and-Coil Intercooler Effectiveness"},
{ Refrigeration_SystemFields::HighStageCompressororCompressorListName, "HighStageCompressororCompressorListName", "High-Stage Compressor or CompressorList Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const Refrigeration_SystemFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Refrigeration_SystemFields> OptionalRefrigeration_SystemFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_REFRIGERATION_SYSTEM_FIELDENUMS_HXX
