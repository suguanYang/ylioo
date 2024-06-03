<Com /> this is JSX
Com this is component

const App = () => {
    // MemoCom is a JSX
    const MemoCom = useMemo(() => <Com />, [])
    
    return (
        <div>
            {MemoCom}
        </div>
    )
}

const App2 = () => {
    // MemoCom is also JSX
    // and call function component inside hooks is not secure if the Com is not immutable
    const MemoCom = useMemo(() => Com(), [])
    
    return (
        <div>
            {MemoCom}
        </div>
    )
}

