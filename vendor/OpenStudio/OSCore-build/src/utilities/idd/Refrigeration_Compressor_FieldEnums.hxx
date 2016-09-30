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

#ifndef UTILITIES_IDD_REFRIGERATION_COMPRESSOR_FIELDENUMS_HXX
#define UTILITIES_IDD_REFRIGERATION_COMPRESSOR_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Refrigeration_CompressorFields
 *  \brief Enumeration of Refrigeration:Compressor's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Refrigeration_CompressorFields, )
#else
class Refrigeration_CompressorFields: public ::EnumBase<Refrigeration_CompressorFields> {
 public: 
  enum domain 
  {
Name, RefrigerationCompressorPowerCurveName, RefrigerationCompressorCapacityCurveName, RatedSuperheat, RatedReturnGasTemperature, RatedLiquidTemperature, RatedSubcooling, EndUseSubcategory, ModeofOperation, TranscriticalCompressorPowerCurveName, TranscriticalCompressorCapacityCurveName,   };
  Refrigeration_CompressorFields()
   : EnumBase<Refrigeration_CompressorFields>(Name) {} 
  Refrigeration_CompressorFields(const std::string &t_name) 
   : EnumBase<Refrigeration_CompressorFields>(t_name) {} 
  Refrigeration_CompressorFields(int t_value) 
   : EnumBase<Refrigeration_CompressorFields>(t_value) {} 
  static std::string enumName() 
  { return "Refrigeration_CompressorFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Refrigeration_CompressorFields>::value()); }
   private:
    friend class EnumBase<Refrigeration_CompressorFields>;
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
{ Refrigeration_CompressorFields::Name, "Name", "Name"},
{ Refrigeration_CompressorFields::RefrigerationCompressorPowerCurveName, "RefrigerationCompressorPowerCurveName", "Refrigeration Compressor Power Curve Name"},
{ Refrigeration_CompressorFields::RefrigerationCompressorCapacityCurveName, "RefrigerationCompressorCapacityCurveName", "Refrigeration Compressor Capacity Curve Name"},
{ Refrigeration_CompressorFields::RatedSuperheat, "RatedSuperheat", "Rated Superheat"},
{ Refrigeration_CompressorFields::RatedReturnGasTemperature, "RatedReturnGasTemperature", "Rated Return Gas Temperature"},
{ Refrigeration_CompressorFields::RatedLiquidTemperature, "RatedLiquidTemperature", "Rated Liquid Temperature"},
{ Refrigeration_CompressorFields::RatedSubcooling, "RatedSubcooling", "Rated Subcooling"},
{ Refrigeration_CompressorFields::EndUseSubcategory, "EndUseSubcategory", "End-Use Subcategory"},
{ Refrigeration_CompressorFields::ModeofOperation, "ModeofOperation", "Mode of Operation"},
{ Refrigeration_CompressorFields::TranscriticalCompressorPowerCurveName, "TranscriticalCompressorPowerCurveName", "Transcritical Compressor Power Curve Name"},
{ Refrigeration_CompressorFields::TranscriticalCompressorCapacityCurveName, "TranscriticalCompressorCapacityCurveName", "Transcritical Compressor Capacity Curve Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const Refrigeration_CompressorFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Refrigeration_CompressorFields> OptionalRefrigeration_CompressorFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_REFRIGERATION_COMPRESSOR_FIELDENUMS_HXX
