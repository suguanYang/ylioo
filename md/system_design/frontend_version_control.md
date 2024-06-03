## Version Specification
For the simplicity and consistency of frontend version control, we consider to formulate this specification. Every frontend project should follow it.

The specification consists of 2 parts: branch strategy and version number.

### Branch Strategy
The branch strategy is as follows:

1. When new release plan is made, a new branch `{releaseNumber}-release-{date}` will be created from the last release branch(`{releaseNumber - 1}-release-{date}`).
2. All **stable**(after fully tested) features will be merged into this branch which belongs to this release plan. 
3. For apps, the branch will published to the `pre`, `prod`, and `performance`. For components this branch is used for publish `{release-number}.X` latest version.

### Version Number
The version number is as follows:

1. When new release plan is made, a new latest version `{releaseNumber}.0` will be published based on last latest version `{releaseNumber - 1}.{latestPatchNumber}`.
2. Changes merged to the branch `{releaseNumber}-release-{date}` need to update the version number of the component. The version number should be `{releaseNumber}.{patchNumber}`. The patchNumber should be increased by 1 for each publish.
3. The `beta` and `alpha` versions are reserved for `test` and `dev` branchs.

## Dependency Version Declaration Constrain
In the development of new release plan, we need to make sure that the dependencies will depend correctly in the `package.json` file. The constraints are:
- On the `{releaseNumber}-release-{date}` branch:
    - Tag version is not allowed.
    - Only Tilde semver range operator is allowed.
    - The version number must great or equal to the `{releaseNumber}`.
    - The specified version number is preferred when you update the dependency.
- on the `test` branch:
    - `beta` tag is allowed.
    - rest are same as `{releaseNumber}.x` version's constrains.
- no constrain on the `dev` branch.

## The automation
When the new release plan is made, the automation script will create the branch and publish the release version automatically.
The steps are:
1. Create a new branch `{releaseNumber}-release-{date}` from the last release branch.
2. Publish the new version `{releaseNumber}.0` based on the last latest version `{releaseNumber - 1}.{latestPatchNumber}`.
3. Update the all the seeyon packages' version number e to `~{releaseNumber}.0` for all apps `package.json`.
4. Trigger the CI/CD pipeline to publish the new branch to the enviroment.

## The devops pipeline checks
All the specification will be checked by the pipeline before the app or component published to the environment.
