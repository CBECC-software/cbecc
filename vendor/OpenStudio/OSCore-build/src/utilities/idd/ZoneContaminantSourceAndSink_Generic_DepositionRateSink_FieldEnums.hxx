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

#ifndef UTILITIES_IDD_ZONECONTAMINANTSOURCEANDSINK_GENERIC_DEPOSITIONRATESINK_FIELDENUMS_HXX
#define UTILITIES_IDD_ZONECONTAMINANTSOURCEANDSINK_GENERIC_DEPOSITIONRATESINK_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class ZoneContaminantSourceAndSink_Generic_DepositionRateSinkFields
 *  \brief Enumeration of ZoneContaminantSourceAndSink:Generic:DepositionRateSink's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(ZoneContaminantSourceAndSink_Generic_DepositionRateSinkFields, )
#else
class ZoneContaminantSourceAndSink_Generic_DepositionRateSinkFields: public ::EnumBase<ZoneContaminantSourceAndSink_Generic_DepositionRateSinkFields> {
 public: 
  enum domain 
  {
Name, ZoneName, DepositionRate, ScheduleName,   };
  ZoneContaminantSourceAndSink_Generic_DepositionRateSinkFields()
   : EnumBase<ZoneContaminantSourceAndSink_Generic_DepositionRateSinkFields>(Name) {} 
  ZoneContaminantSourceAndSink_Generic_DepositionRateSinkFields(const std::string &t_name) 
   : EnumBase<ZoneContaminantSourceAndSink_Generic_DepositionRateSinkFields>(t_name) {} 
  ZoneContaminantSourceAndSink_Generic_DepositionRateSinkFields(int t_value) 
   : EnumBase<ZoneContaminantSourceAndSink_Generic_DepositionRateSinkFields>(t_value) {} 
  static std::string enumName() 
  { return "ZoneContaminantSourceAndSink_Generic_DepositionRateSinkFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ZoneContaminantSourceAndSink_Generic_DepositionRateSinkFields>::value()); }
   private:
    friend class EnumBase<ZoneContaminantSourceAndSink_Generic_DepositionRateSinkFields>;
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
{ ZoneContaminantSourceAndSink_Generic_DepositionRateSinkFields::Name, "Name", "Name"},
{ ZoneContaminantSourceAndSink_Generic_DepositionRateSinkFields::ZoneName, "ZoneName", "Zone Name"},
{ ZoneContaminantSourceAndSink_Generic_DepositionRateSinkFields::DepositionRate, "DepositionRate", "Deposition Rate"},
{ ZoneContaminantSourceAndSink_Generic_DepositionRateSinkFields::ScheduleName, "ScheduleName", "Schedule Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const ZoneContaminantSourceAndSink_Generic_DepositionRateSinkFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ZoneContaminantSourceAndSink_Generic_DepositionRateSinkFields> OptionalZoneContaminantSourceAndSink_Generic_DepositionRateSinkFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_ZONECONTAMINANTSOURCEANDSINK_GENERIC_DEPOSITIONRATESINK_FIELDENUMS_HXX
