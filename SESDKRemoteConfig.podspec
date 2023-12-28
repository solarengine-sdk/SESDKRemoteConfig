#
# Be sure to run `pod lib lint SESDKRemoteConfig.podspec' to ensure this is a
# valid spec before submitting.
#
# Any lines starting with a # are optional, but their use is encouraged
# To learn more about a Podspec see https://guides.cocoapods.org/syntax/podspec.html
#

Pod::Spec.new do |s|
  s.name             = 'SESDKRemoteConfig'
  s.version          = '1.2.6.1'
  s.summary          = 'Official SESDKRemoteConfig for iOS.'

# This description is used to generate tags and improve search results.
#   * Think: What does it do? Why did you write it? What is the focus?
#   * Try to keep it short, snappy and to the point.
#   * Write the description between the DESC delimiters below.
#   * Finally, don't worry about the indent, CocoaPods strips it!

  s.description      = <<-DESC
TODO: Add long description of the pod here.
                       DESC

  s.homepage         = 'https://www.solar-engine.com'
  s.license          =  { :type => "Apache License, Version 2.0" }
  s.summary          = 'Official SolarEngineSDK for iOS.'
  s.author           = { 'solarengine-sdk' => 'sdk@solar-engine.com' }
  s.source           = { :git => 'https://github.com/solarengine-sdk/SESDKRemoteConfig.git', :tag => s.version.to_s }
  # s.social_media_url = 'https://twitter.com/<TWITTER_USERNAME>'

  s.ios.deployment_target = '11.0'

  s.vendored_frameworks = 'SESDKRemoteConfig/*.framework'
  # s.frameworks = ""
  # s.libraries = ""
  s.requires_arc = true
  
  s.pod_target_xcconfig = { 'EXCLUDED_ARCHS[sdk=iphonesimulator*]' => 'arm64' }
  s.user_target_xcconfig = { 'EXCLUDED_ARCHS[sdk=iphonesimulator*]' => 'arm64' }
end
