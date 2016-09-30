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

#ifndef UTILITIES_IDD_AIRFLOWNETWORK_DISTRIBUTION_NODE_FIELDENUMS_HXX
#define UTILITIES_IDD_AIRFLOWNETWORK_DISTRIBUTION_NODE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class AirflowNetwork_Distribution_NodeFields
 *  \brief Enumeration of AirflowNetwork:Distribution:Node's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(AirflowNetwork_Distribution_NodeFields, )
#else
class AirflowNetwork_Distribution_NodeFields: public ::EnumBase<AirflowNetwork_Distribution_NodeFields> {
 public: 
  enum domain 
  {
Name, ComponentNameorNodeName, ComponentObjectTypeorNodeType, NodeHeight,   };
  AirflowNetwork_Distribution_NodeFields()
   : EnumBase<AirflowNetwork_Distribution_NodeFields>(Name) {} 
  AirflowNetwork_Distribution_NodeFields(const std::string &t_name) 
   : EnumBase<AirflowNetwork_Distribution_NodeFields>(t_name) {} 
  AirflowNetwork_Distribution_NodeFields(int t_value) 
   : EnumBase<AirflowNetwork_Distribution_NodeFields>(t_value) {} 
  static std::string enumName() 
  { return "AirflowNetwork_Distribution_NodeFields"; }
  domain value() const { return static_cast<domain>(EnumBase<AirflowNetwork_Distribution_NodeFields>::value()); }
   private:
    friend class EnumBase<AirflowNetwork_Distribution_NodeFields>;
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
{ AirflowNetwork_Distribution_NodeFields::Name, "Name", "Name"},
{ AirflowNetwork_Distribution_NodeFields::ComponentNameorNodeName, "ComponentNameorNodeName", "Component Name or Node Name"},
{ AirflowNetwork_Distribution_NodeFields::ComponentObjectTypeorNodeType, "ComponentObjectTypeorNodeType", "Component Object Type or Node Type"},
{ AirflowNetwork_Distribution_NodeFields::NodeHeight, "NodeHeight", "Node Height"},
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
  inline std::ostream &operator<<(std::ostream &os, const AirflowNetwork_Distribution_NodeFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<AirflowNetwork_Distribution_NodeFields> OptionalAirflowNetwork_Distribution_NodeFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_AIRFLOWNETWORK_DISTRIBUTION_NODE_FIELDENUMS_HXX
