Pod::Spec.new do |s|

  s.name         = "AferoSofthubRelease"
  s.module_name  = "AferoSofthubRelease"
  s.version      = "1.1.0"
  s.summary      = "Afero hub library (binary distribution)"
  s.description  = "Softhub support for Afero devices."
  s.homepage     = "https://github.com/aferodeveloper/hubby"
  s.license      = "Proprietary"
  s.author             = { "Stephen Sewerynek" => "stephen@kiban.io" }

  s.ios.deployment_target = "8.4"
  s.osx.deployment_target = "10.10"
  s.source       = { :git => "git@github.com:aferodeveloper/AferoSofthubRelease.git", :tag => "#{s.version}" }

  ARCHIVE_ROOT = "archive/hubby/pkg/src"

  s.source_files = "#{ARCHIVE_ROOT}/cocoa/*"
  s.public_header_files = "#{ARCHIVE_ROOT}/cocoa/AferoSofthub.h"
  s.frameworks = 'CoreBluetooth', 'SystemConfiguration'
  s.libraries = "Hubby", "crypto", "curl", "event", "event_core", "event_pthreads", "json-c", "ssl", "z", "stdc++"

  LIBS_DIR = "#{ARCHIVE_ROOT}/ios/libs-debug"
  s.preserve_paths = LIBS_DIR

  s.vendored_libraries = [
    "libHubby.a",
    "libcrypto.a",
    "libcurl.a",
    "libevent.a",
    "libevent_core.a",
    "libevent_pthreads.a",
    "libjson-c.a",
    "libssl.a",
    "libz.a"
  ].map { |p| "#{LIBS_DIR}/#{p}" }
  
  s.pod_target_xcconfig = {
    'LIBRARY_SEARCH_PATHS' => "$(inherited) #{LIBS_DIR}",
  }

end



  #MY_LIB_ROOT = "${PODS_TARGET_SRCROOT}/thirdparty-ios"
  #MY_HEADER_ROOT = "${PODS_TARGET_SRCROOT}/thirdparty-ios"

  #header_search_paths = '$(inherited) ' + [
  #  'json-c-0.12/ios/include',
  #  'curl-7.50.3/ios/prebuilt-with-ssl/include',
  #  'libevent-2.0.22-stable/ios/include',
  #  'openssl-1.0.1u/ios/include'
  #  ].map { |p| MY_HEADER_ROOT + "/" + p }.join(" ")
#
#  library_search_paths = '$(inherited) ' + [
#    'curl-7.50.3/ios/prebuilt-with-ssl',
#    'json-c-0.12/ios/libs',
##    'libevent-2.0.22-stable/ios/lib',
#    'openssl-1.0.1u/ios/lib',
#    'zlib-1.2.8/ios/lib'
#    ].map { |p| MY_LIB_ROOT + "/" + p }.join(" ")
#
