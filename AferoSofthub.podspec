Pod::Spec.new do |s|

  s.name         = "AferoSofthub"
  s.module_name  = "AferoSofthub"
  s.version      = "1.1.0"
  s.summary      = "Afero hub library (binary distribution)"
  s.description  = "Softhub support for Afero devices."
  s.homepage     = "https://github.com/aferodeveloper/hubby"
  s.license      = "Proprietary"
  s.author             = { "Afero, Inc." => "developer@afero.io" }

  s.ios.deployment_target = "9.3"
  s.source       = { :git => "git@github.com:aferodeveloper/AferoSofthub.git", :tag => "#{s.version}" }

  s.weak_frameworks = 'CoreBluetooth', 'SystemConfiguration'
  s.vendored_frameworks = "AferoSofthub.framework"

end
