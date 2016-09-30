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

#ifndef UTILITIES_IDD_IDDFACTORY_HXX
#define UTILITIES_IDD_IDDFACTORY_HXX

#include <utilities/UtilitiesAPI.hpp>

#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/IddFile.hpp>
#include <utilities/idd/IddEnums.hpp>
#include <utilities/idd/IddEnums.hxx>

#include <utilities/core/Singleton.hpp>
#include <utilities/core/Compare.hpp>
#include <utilities/core/Logger.hpp>
#include <QMutex>

#include <map>

namespace openstudio{

/** IddFactorySingleton can return \link IddObject IddObjects\endlink and \link IddFile
 *  IddFiles\endlink for the current version of EnergyPlus and OpenStudio. It can return \link IddFile 
 *  IddFiles\endlink only (no link with other methods in this class, for instance, no 
 *  by-IddObjectType access to individual \link IddObject IddObjects\endlink) for 
 *  previous versions of OpenStudio, back to version 0.7.0. It also supports the default IddObject 
 *  type, Catchall, which is provided to enable the display of IdfObjects with misspelled type 
 *  names, and a CommentOnly object. Its primary function is to establish a single set of IDD schema 
 *  across all of OpenStudio, thereby ensuring consistency and reducing file I-O. 
 *  
 *  IddFactorySingleton should be used through the IddFactory typedef as in
 *  \code
 *  IddFile osIddFile = IddFactory::instance().iddFile(IddFileType::OpenStudio);
 *  \endcode */
class UTILITIES_API IddFactorySingleton  {

  friend class Singleton<IddFactorySingleton>;

 public:
  /** @name Getters */
  //@{ 

  /** Get the file version. Throws if fileType == IddFileType::UserCustom or 
   *  IddFileType::WholeFactory. */
  std::string getVersion(IddFileType fileType) const;

  /** Get the file header. Throws if fileType == IddFileType::UserCustom or 
   *  IddFileType::WholeFactory. */
  std::string getHeader(IddFileType fileType) const;

  /** Return all \link IddObject IddObjects\endlink registered in factory. */
  std::vector<IddObject> objects() const;

  /** Return all \link IddObject IddObjects\endlink in IddFileType type. */
  std::vector<IddObject> getObjects(IddFileType fileType) const;

  /** Return all groups in the factory (e.g. "" and "Simulation Parameters"). */
  std::vector<std::string> groups() const;

  /** Return all groups in fileType. */
  std::vector<std::string> getGroups(IddFileType fileType) const;

  /** Return all \link IddObject IddObjects\endlink in group (e.g. "Simulation Parameters"). */
  std::vector<IddObject> getObjectsInGroup(const std::string& group) const;

  /** Return all \link IddObject IddObjects\endlink in group and fileType. */
  std::vector<IddObject> getObjectsInGroup(const std::string& group, IddFileType fileType) const;

  /** Return all \link IddObject IddObjects\endlink that match objectRegex. */
  std::vector<IddObject> getObjects(const boost::regex& objectRegex) const;

  /** Return all \link IddObject IddObjects\endlink that match objectRegex and are in fileType. */
  std::vector<IddObject> getObjects(const boost::regex& objectRegex, IddFileType fileType) const;

  /** Returns the version IddObject for fileType. Throws if fileType == IddFileType::UserCustom 
   *  or IddFileType::WholeFactory. */
  IddObject getVersionObject(IddFileType fileType) const;

  /** Return the IddObject with .name() objectName, if it exists in the factory. */
  boost::optional<IddObject> getObject(const std::string& objectName) const;

  /** Return the IddObject corresponding to objectType. Returns false if type == 
   *  IddObjectType::UserCustom. */
  boost::optional<IddObject> getObject(IddObjectType objectType) const;

  /** Return all objects in the factory that are required. */
  std::vector<IddObject> requiredObjects() const;

  /** Return all objects in IddFile fileType that are required. */
  std::vector<IddObject> getRequiredObjects(IddFileType fileType) const;

  /** Return all objects in the factory that are unique. */
  std::vector<IddObject> uniqueObjects() const;

  /** Return all objects in IddFile fileType that are unique. */
  std::vector<IddObject> getUniqueObjects(IddFileType fileType) const;

  /** Return the (current) IddFile corresponding to type. */
  IddFile getIddFile(IddFileType fileType) const;

  /** Return the IddFile corresponding to type and version. Unless version is equal to 
   *  VersionString(getVersion(fileType)), files are loaded from disk and returned as 
   *  IddFileType::UserCustom, to distinguish them from the IDD information wrapped by 
   *  the IddFactory. At this time, only IddFileType::OpenStudio files are supported, 
   *  and only for valid version identifiers >= VersionString("0.7.0"). Returns false 
   *  in all other cases. */
  boost::optional<IddFile> getIddFile(IddFileType fileType, const VersionString& version) const;

  //@}
  /** @name Queries */
  //@{

  /** Returns true if IddObject of objectType belongs to IddFile of fileType. 
   *  IddObjectType::Catchall is in no \link IddFile IddFiles\endlink; 
   *  IddObjectType::CommentOnly is in all \link IddFile IddFiles\endlink. */
  bool isInFile(IddObjectType objectType, IddFileType fileType) const;

  //@}
 private:

  IddFactorySingleton();
  void registerEnergyPlusObjectsInCallbackMap();
  void registerOpenStudioObjectsInCallbackMap();

  REGISTER_LOGGER("utilities.idd.IddFactory");

  typedef std::function<IddObject ()> CreateIddObjectCallback;
  typedef std::map<IddObjectType,CreateIddObjectCallback> IddObjectCallbackMap;
  IddObjectCallbackMap m_callbackMap;
  mutable QMutex m_callbackmutex;

  typedef std::multimap<IddObjectType,IddFileType> IddObjectSourceFileMap;
  IddObjectSourceFileMap m_sourceFileMap;

  mutable std::map<VersionString,IddFile> m_osIddFiles;
};

#if _WIN32 || _MSC_VER
  // Explicitly instantiate and export IddFactorySingleton Singleton template instance
  // so that the same instance is shared between DLLs that link to Utilities.dll.
  UTILITIES_TEMPLATE_EXT template class UTILITIES_API openstudio::Singleton<IddFactorySingleton>;
#endif

/** Convenience typedef for accessing IddFactorySingleton. Usage:
 *  \code
 *  unsigned n = IddFactory::instance().objects().size();
 *  \endcode
 *  
 *  \relates IddFactorySingleton */
typedef openstudio::Singleton<IddFactorySingleton> IddFactory;

} // openstudio

#endif //UTILITIES_IDD_IDDFACTORY_HXX
