/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) 2008-2023, Alliance for Sustainable Energy, LLC, and other contributors. All rights reserved.
*
*  Redistribution and use in source and binary forms, with or without modification, are permitted provided that the
*  following conditions are met:
*
*  (1) Redistributions of source code must retain the above copyright notice, this list of conditions and the following
*  disclaimer.
*
*  (2) Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following
*  disclaimer in the documentation and/or other materials provided with the distribution.
*
*  (3) Neither the name of the copyright holder nor the names of any contributors may be used to endorse or promote products
*  derived from this software without specific prior written permission from the respective party.
*
*  (4) Other than as required in clauses (1) and (2), distributions in any form of modifications or other derivative works
*  may not use the "OpenStudio" trademark, "OS", "os", or any other confusingly similar designation without specific prior
*  written permission from Alliance for Sustainable Energy, LLC.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER(S) AND ANY CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
*  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
*  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER(S), ANY CONTRIBUTORS, THE UNITED STATES GOVERNMENT, OR THE UNITED
*  STATES DEPARTMENT OF ENERGY, NOR ANY OF THEIR EMPLOYEES, BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
*  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
*  USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
*  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
*  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
***********************************************************************************************************************/

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
