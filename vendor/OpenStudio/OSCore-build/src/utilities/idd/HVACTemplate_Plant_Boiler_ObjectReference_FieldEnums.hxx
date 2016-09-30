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

#ifndef UTILITIES_IDD_HVACTEMPLATE_PLANT_BOILER_OBJECTREFERENCE_FIELDENUMS_HXX
#define UTILITIES_IDD_HVACTEMPLATE_PLANT_BOILER_OBJECTREFERENCE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class HVACTemplate_Plant_Boiler_ObjectReferenceFields
 *  \brief Enumeration of HVACTemplate:Plant:Boiler:ObjectReference's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(HVACTemplate_Plant_Boiler_ObjectReferenceFields, )
#else
class HVACTemplate_Plant_Boiler_ObjectReferenceFields: public ::EnumBase<HVACTemplate_Plant_Boiler_ObjectReferenceFields> {
 public: 
  enum domain 
  {
Name, BoilerObjectType, BoilerName, Priority, TemplatePlantLoopType,   };
  HVACTemplate_Plant_Boiler_ObjectReferenceFields()
   : EnumBase<HVACTemplate_Plant_Boiler_ObjectReferenceFields>(Name) {} 
  HVACTemplate_Plant_Boiler_ObjectReferenceFields(const std::string &t_name) 
   : EnumBase<HVACTemplate_Plant_Boiler_ObjectReferenceFields>(t_name) {} 
  HVACTemplate_Plant_Boiler_ObjectReferenceFields(int t_value) 
   : EnumBase<HVACTemplate_Plant_Boiler_ObjectReferenceFields>(t_value) {} 
  static std::string enumName() 
  { return "HVACTemplate_Plant_Boiler_ObjectReferenceFields"; }
  domain value() const { return static_cast<domain>(EnumBase<HVACTemplate_Plant_Boiler_ObjectReferenceFields>::value()); }
   private:
    friend class EnumBase<HVACTemplate_Plant_Boiler_ObjectReferenceFields>;
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
{ HVACTemplate_Plant_Boiler_ObjectReferenceFields::Name, "Name", "Name"},
{ HVACTemplate_Plant_Boiler_ObjectReferenceFields::BoilerObjectType, "BoilerObjectType", "Boiler Object Type"},
{ HVACTemplate_Plant_Boiler_ObjectReferenceFields::BoilerName, "BoilerName", "Boiler Name"},
{ HVACTemplate_Plant_Boiler_ObjectReferenceFields::Priority, "Priority", "Priority"},
{ HVACTemplate_Plant_Boiler_ObjectReferenceFields::TemplatePlantLoopType, "TemplatePlantLoopType", "Template Plant Loop Type"},
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
  inline std::ostream &operator<<(std::ostream &os, const HVACTemplate_Plant_Boiler_ObjectReferenceFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<HVACTemplate_Plant_Boiler_ObjectReferenceFields> OptionalHVACTemplate_Plant_Boiler_ObjectReferenceFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_HVACTEMPLATE_PLANT_BOILER_OBJECTREFERENCE_FIELDENUMS_HXX
