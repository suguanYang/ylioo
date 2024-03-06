const useState = () => {
    const stateDependencies = useRef({}).current
    const error = cached.error


    return {
      get data() {
        stateDependencies.data = true
        return returnedData
      },
      get error() {
        stateDependencies.error = true
        return error
      },
      get isValidating() {
        stateDependencies.isValidating = true
        return isValidating
      },
      get isLoading() {
        stateDependencies.isLoading = true
        return isLoading
      }
    } as SWRResponse<Data, Error>
  }