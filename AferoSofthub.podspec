Pod::Spec.new do |s|

  s.name         = "AferoSofthub"
  s.module_name  = "AferoSofthub"
  s.version      = "1.1.0"
  s.summary      = "Afero hub library (binary distribution)"
  s.description  = "Softhub support for Afero devices."
  s.homepage     = "https://github.com/aferodeveloper/hubby"
  s.license      = "Proprietary"
  s.author             = { "Afero, Inc." => "developer@afero.io" }

  s.ios.deployment_target = "8.4"
  s.osx.deployment_target = "10.10"
  s.source       = { :git => "git@github.com:aferodeveloper/AferoSofthub.git", :tag => "#{s.version}" }

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
