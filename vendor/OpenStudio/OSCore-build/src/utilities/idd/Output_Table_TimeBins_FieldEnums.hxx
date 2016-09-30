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

#ifndef UTILITIES_IDD_OUTPUT_TABLE_TIMEBINS_FIELDENUMS_HXX
#define UTILITIES_IDD_OUTPUT_TABLE_TIMEBINS_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Output_Table_TimeBinsFields
 *  \brief Enumeration of Output:Table:TimeBins's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Output_Table_TimeBinsFields, )
#else
class Output_Table_TimeBinsFields: public ::EnumBase<Output_Table_TimeBinsFields> {
 public: 
  enum domain 
  {
KeyValue, VariableName, IntervalStart, IntervalSize, IntervalCount, ScheduleName, VariableType,   };
  Output_Table_TimeBinsFields()
   : EnumBase<Output_Table_TimeBinsFields>(KeyValue) {} 
  Output_Table_TimeBinsFields(const std::string &t_name) 
   : EnumBase<Output_Table_TimeBinsFields>(t_name) {} 
  Output_Table_TimeBinsFields(int t_value) 
   : EnumBase<Output_Table_TimeBinsFields>(t_value) {} 
  static std::string enumName() 
  { return "Output_Table_TimeBinsFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Output_Table_TimeBinsFields>::value()); }
   private:
    friend class EnumBase<Output_Table_TimeBinsFields>;
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
{ Output_Table_TimeBinsFields::KeyValue, "KeyValue", "Key Value"},
{ Output_Table_TimeBinsFields::VariableName, "VariableName", "Variable Name"},
{ Output_Table_TimeBinsFields::IntervalStart, "IntervalStart", "Interval Start"},
{ Output_Table_TimeBinsFields::IntervalSize, "IntervalSize", "Interval Size"},
{ Output_Table_TimeBinsFields::IntervalCount, "IntervalCount", "Interval Count"},
{ Output_Table_TimeBinsFields::ScheduleName, "ScheduleName", "Schedule Name"},
{ Output_Table_TimeBinsFields::VariableType, "VariableType", "Variable Type"},
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
  inline std::ostream &operator<<(std::ostream &os, const Output_Table_TimeBinsFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Output_Table_TimeBinsFields> OptionalOutput_Table_TimeBinsFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OUTPUT_TABLE_TIMEBINS_FIELDENUMS_HXX
