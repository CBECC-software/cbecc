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

#ifndef UTILITIES_IDD_OUTPUT_PREPROCESSORMESSAGE_FIELDENUMS_HXX
#define UTILITIES_IDD_OUTPUT_PREPROCESSORMESSAGE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Output_PreprocessorMessageFields
 *  \brief Enumeration of Output:PreprocessorMessage's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Output_PreprocessorMessageFields, )
#else
class Output_PreprocessorMessageFields: public ::EnumBase<Output_PreprocessorMessageFields> {
 public: 
  enum domain 
  {
PreprocessorName, ErrorSeverity, MessageLine1, MessageLine2, MessageLine3, MessageLine4, MessageLine5, MessageLine6, MessageLine7, MessageLine8, MessageLine9, MessageLine10,   };
  Output_PreprocessorMessageFields()
   : EnumBase<Output_PreprocessorMessageFields>(PreprocessorName) {} 
  Output_PreprocessorMessageFields(const std::string &t_name) 
   : EnumBase<Output_PreprocessorMessageFields>(t_name) {} 
  Output_PreprocessorMessageFields(int t_value) 
   : EnumBase<Output_PreprocessorMessageFields>(t_value) {} 
  static std::string enumName() 
  { return "Output_PreprocessorMessageFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Output_PreprocessorMessageFields>::value()); }
   private:
    friend class EnumBase<Output_PreprocessorMessageFields>;
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
{ Output_PreprocessorMessageFields::PreprocessorName, "PreprocessorName", "Preprocessor Name"},
{ Output_PreprocessorMessageFields::ErrorSeverity, "ErrorSeverity", "Error Severity"},
{ Output_PreprocessorMessageFields::MessageLine1, "MessageLine1", "Message Line 1"},
{ Output_PreprocessorMessageFields::MessageLine2, "MessageLine2", "Message Line 2"},
{ Output_PreprocessorMessageFields::MessageLine3, "MessageLine3", "Message Line 3"},
{ Output_PreprocessorMessageFields::MessageLine4, "MessageLine4", "Message Line 4"},
{ Output_PreprocessorMessageFields::MessageLine5, "MessageLine5", "Message Line 5"},
{ Output_PreprocessorMessageFields::MessageLine6, "MessageLine6", "Message Line 6"},
{ Output_PreprocessorMessageFields::MessageLine7, "MessageLine7", "Message Line 7"},
{ Output_PreprocessorMessageFields::MessageLine8, "MessageLine8", "Message Line 8"},
{ Output_PreprocessorMessageFields::MessageLine9, "MessageLine9", "Message Line 9"},
{ Output_PreprocessorMessageFields::MessageLine10, "MessageLine10", "Message Line 10"},
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
  inline std::ostream &operator<<(std::ostream &os, const Output_PreprocessorMessageFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Output_PreprocessorMessageFields> OptionalOutput_PreprocessorMessageFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OUTPUT_PREPROCESSORMESSAGE_FIELDENUMS_HXX
