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

#ifndef UTILITIES_IDD_AIRFLOWNETWORK_INTRAZONE_LINKAGE_FIELDENUMS_HXX
#define UTILITIES_IDD_AIRFLOWNETWORK_INTRAZONE_LINKAGE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class AirflowNetwork_IntraZone_LinkageFields
 *  \brief Enumeration of AirflowNetwork:IntraZone:Linkage's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(AirflowNetwork_IntraZone_LinkageFields, )
#else
class AirflowNetwork_IntraZone_LinkageFields: public ::EnumBase<AirflowNetwork_IntraZone_LinkageFields> {
 public: 
  enum domain 
  {
Name, Node1Name, Node2Name, ComponentName, AirflowNetwork_MultiZone_SurfaceName,   };
  AirflowNetwork_IntraZone_LinkageFields()
   : EnumBase<AirflowNetwork_IntraZone_LinkageFields>(Name) {} 
  AirflowNetwork_IntraZone_LinkageFields(const std::string &t_name) 
   : EnumBase<AirflowNetwork_IntraZone_LinkageFields>(t_name) {} 
  AirflowNetwork_IntraZone_LinkageFields(int t_value) 
   : EnumBase<AirflowNetwork_IntraZone_LinkageFields>(t_value) {} 
  static std::string enumName() 
  { return "AirflowNetwork_IntraZone_LinkageFields"; }
  domain value() const { return static_cast<domain>(EnumBase<AirflowNetwork_IntraZone_LinkageFields>::value()); }
   private:
    friend class EnumBase<AirflowNetwork_IntraZone_LinkageFields>;
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
{ AirflowNetwork_IntraZone_LinkageFields::Name, "Name", "Name"},
{ AirflowNetwork_IntraZone_LinkageFields::Node1Name, "Node1Name", "Node 1 Name"},
{ AirflowNetwork_IntraZone_LinkageFields::Node2Name, "Node2Name", "Node 2 Name"},
{ AirflowNetwork_IntraZone_LinkageFields::ComponentName, "ComponentName", "Component Name"},
{ AirflowNetwork_IntraZone_LinkageFields::AirflowNetwork_MultiZone_SurfaceName, "AirflowNetwork_MultiZone_SurfaceName", "AirflowNetwork:MultiZone:Surface Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const AirflowNetwork_IntraZone_LinkageFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<AirflowNetwork_IntraZone_LinkageFields> OptionalAirflowNetwork_IntraZone_LinkageFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_AIRFLOWNETWORK_INTRAZONE_LINKAGE_FIELDENUMS_HXX
