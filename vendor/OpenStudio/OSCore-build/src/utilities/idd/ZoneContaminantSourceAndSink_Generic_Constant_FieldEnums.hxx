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

#ifndef UTILITIES_IDD_ZONECONTAMINANTSOURCEANDSINK_GENERIC_CONSTANT_FIELDENUMS_HXX
#define UTILITIES_IDD_ZONECONTAMINANTSOURCEANDSINK_GENERIC_CONSTANT_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class ZoneContaminantSourceAndSink_Generic_ConstantFields
 *  \brief Enumeration of ZoneContaminantSourceAndSink:Generic:Constant's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(ZoneContaminantSourceAndSink_Generic_ConstantFields, )
#else
class ZoneContaminantSourceAndSink_Generic_ConstantFields: public ::EnumBase<ZoneContaminantSourceAndSink_Generic_ConstantFields> {
 public: 
  enum domain 
  {
Name, ZoneName, DesignGenerationRate, GenerationScheduleName, DesignRemovalCoefficient, RemovalScheduleName,   };
  ZoneContaminantSourceAndSink_Generic_ConstantFields()
   : EnumBase<ZoneContaminantSourceAndSink_Generic_ConstantFields>(Name) {} 
  ZoneContaminantSourceAndSink_Generic_ConstantFields(const std::string &t_name) 
   : EnumBase<ZoneContaminantSourceAndSink_Generic_ConstantFields>(t_name) {} 
  ZoneContaminantSourceAndSink_Generic_ConstantFields(int t_value) 
   : EnumBase<ZoneContaminantSourceAndSink_Generic_ConstantFields>(t_value) {} 
  static std::string enumName() 
  { return "ZoneContaminantSourceAndSink_Generic_ConstantFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ZoneContaminantSourceAndSink_Generic_ConstantFields>::value()); }
   private:
    friend class EnumBase<ZoneContaminantSourceAndSink_Generic_ConstantFields>;
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
{ ZoneContaminantSourceAndSink_Generic_ConstantFields::Name, "Name", "Name"},
{ ZoneContaminantSourceAndSink_Generic_ConstantFields::ZoneName, "ZoneName", "Zone Name"},
{ ZoneContaminantSourceAndSink_Generic_ConstantFields::DesignGenerationRate, "DesignGenerationRate", "Design Generation Rate"},
{ ZoneContaminantSourceAndSink_Generic_ConstantFields::GenerationScheduleName, "GenerationScheduleName", "Generation Schedule Name"},
{ ZoneContaminantSourceAndSink_Generic_ConstantFields::DesignRemovalCoefficient, "DesignRemovalCoefficient", "Design Removal Coefficient"},
{ ZoneContaminantSourceAndSink_Generic_ConstantFields::RemovalScheduleName, "RemovalScheduleName", "Removal Schedule Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const ZoneContaminantSourceAndSink_Generic_ConstantFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ZoneContaminantSourceAndSink_Generic_ConstantFields> OptionalZoneContaminantSourceAndSink_Generic_ConstantFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_ZONECONTAMINANTSOURCEANDSINK_GENERIC_CONSTANT_FIELDENUMS_HXX
